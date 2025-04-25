//
// Created by Tuna Öztürk on 30.03.2025.
//

#include "WindowSystem.h"
#include <iostream>

WindowSystem::WindowSystem(int width, int height, const char *title)
{
    if (!initGLFW() || !createWindow(width, height, title))
    {
        // Handle failure (throw exception or set a flag)
    }
    else
    {
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
    }
}

WindowSystem::~WindowSystem()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool WindowSystem::initGLFW()
{
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // OpenGL hints can be set here
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _WIN32
    // Windows'ta pencere taşınırken bile render işlemi devam eder
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
#endif

    return true;
}
bool WindowSystem::createWindow(int width, int height, const char *title)
{
    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << std::endl;
        return false;
    }

    // Query the actual framebuffer size and set the viewport accordingly.
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(m_Window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);
    glfwSetKeyCallback(m_Window, keyCallback);
    // Enable V-Sync
    glfwSwapInterval(1);

    return true;
}

bool WindowSystem::shouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void WindowSystem::swapBuffers() const
{
    glfwSwapBuffers(m_Window);
}

void WindowSystem::pollEvents()
{
    glfwPollEvents();
}

GLFWwindow *WindowSystem::getWindow() const
{
    return m_Window;
}

// Static callback functions
void WindowSystem::errorCallback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void WindowSystem::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    std::cout <<aspectRatio << "\n";
}

void WindowSystem::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

float WindowSystem::aspectRatio = 16.f / 9.f;

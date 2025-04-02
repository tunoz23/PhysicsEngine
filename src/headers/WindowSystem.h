//
// Created by Tuna Öztürk on 30.03.2025.
//
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowSystem {
public:
    WindowSystem(int width, int height, const char* title);
    ~WindowSystem();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents();
    GLFWwindow* getWindow() const;

private:
    GLFWwindow* m_Window;

    static void errorCallback(int error, const char* description);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool initGLFW();
    bool createWindow(int width, int height, const char* title);
};

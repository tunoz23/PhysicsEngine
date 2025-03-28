#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/Shader.h"

// Error callback
void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

// Window size change callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Keyboard input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Set error callback
    glfwSetErrorCallback(error_callback);
     // OpenGL 4.2 Core Profile for other systems

    #ifdef __APPLE__

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    #endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL GLFW Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Activate OpenGL context
    glfwMakeContextCurrent(window);
    
    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Display OpenGL version and GPU info
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
    
    // Set viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    
    // Enable V-Sync
    glfwSwapInterval(1);


	Shader shader(RESOURCE_PATH "Shaders/DefaultVertex.glsl", RESOURCE_PATH "Shaders/DefaultFragment.glsl");

    uint32_t vao,vbo;
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		shader.use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
        // Drawing code will go here
        
        // Swap buffers and process events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Clean up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

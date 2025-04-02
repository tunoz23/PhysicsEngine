#include "WindowSystem.h"
#include "Scene.h"
#include "headers/Shader.h"



int main() {
    WindowSystem windowSystem(1024, 576, "PhysicsEngine");

    Shader shader(RESOURCE_PATH "Shaders/DefaultVertex.glsl", RESOURCE_PATH "Shaders/DefaultFragment.glsl");


    Scene scene(shader);
    constexpr float color = 44/255.0f;

    float lastFrameTime = glfwGetTime();
    float currentFrameTime = 0.0f;
    float dt = 0.0f;

    //TO DO: the circle doesn't work.

   while (!windowSystem.shouldClose()) {
        currentFrameTime = glfwGetTime();
        dt = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;


        glClearColor(color, color, color, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.main(dt);

        windowSystem.swapBuffers();
        windowSystem.pollEvents();
    }
    
    return 0;
}

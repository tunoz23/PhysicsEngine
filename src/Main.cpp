#include "Scene.h"
#include "WindowSystem.h"
#include "headers/Shader.h"

int main()
{
    WindowSystem windowSystem(1024, 576, "PhysicsEngine");
    // RenderSystem::aspectRatio = WindowSystem::aspectRatio;
    Shader shader(RESOURCE_PATH "Shaders/DefaultVertex.glsl", RESOURCE_PATH "Shaders/DefaultFragment.glsl");

    Scene scene(shader);

    constexpr float color = 44 / 255.0f;

    double lastFrameTime = glfwGetTime();
    double currentFrameTime = 0.0f;
    double dt = 0.0f;

    while (!windowSystem.shouldClose())
    {

        currentFrameTime = glfwGetTime();
        dt = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        windowSystem.pollEvents();

        glClearColor(color, color, color, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.main(dt);

        windowSystem.swapBuffers();
    }

    return 0;
}

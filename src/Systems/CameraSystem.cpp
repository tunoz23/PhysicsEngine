#include <iostream>

#include "CameraComponent.h"
#include "CameraSystem.h"
#include "TransformComponent.h"
#include "ActiveCameraData.h"
void CameraSystem::update(entt::registry &registry)
{
    // Query entity with CameraComponent and TransformComponent
    auto view = registry.view<CameraComponent, TransformComponent>();

    if (view.begin() == view.end())
    {
        std::cerr << "Warning: No camera entity found!" << std::endl;
        return;
    }

    // Assume first camera entity
    auto entity = view.front();
    const auto &camComp = view.get<CameraComponent>(entity);
    const auto &camTf = view.get<TransformComponent>(entity);

    // Build view matrix from transform
    glm::vec3 camPosition = camTf.position;
    // Derive front vector from rotation quaternion
    glm::vec3 camFront =  glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp =  glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 viewMat = glm::lookAt(camPosition, glm::vec3(0.f), camUp);

    // Build projection matrix
    float ratio = camComp.aspectRatio;
    glm::mat4 projMat = glm::perspective(glm::radians(camComp.fov), ratio, camComp.near, camComp.far);


    registry.ctx().insert_or_assign<ActiveCameraData>(ActiveCameraData{.projection = projMat, .view = viewMat});
}

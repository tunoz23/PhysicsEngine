// CameraSystem.h
#pragma once

#include <entt.hpp>
#include <glad/glad.h> // or appropriate loader
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>





class CameraSystem
{
  public:

    // Update view/projection matrices each frame
    void update(entt::registry &registry);


};

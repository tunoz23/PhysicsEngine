//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <RenderSystem.h>
#include <Shader.h>
#include <entt.hpp>

#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "CameraSystem.h"

class Scene
{
  public:
    RenderSystem renderSystem;
    PhysicsSystem physicsSystem;
    CollisionSystem collisionSystem;
    CameraSystem cameraSystem;

    Scene(Shader shader);
    ~Scene() = default;

    void main(double dt);

  private:
    entt::registry m_Registry;
    entt::dispatcher m_Dispatcher;
};

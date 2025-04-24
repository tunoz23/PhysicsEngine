//
// Created by Tuna Öztürk on 30.03.2025.
//

#pragma once
#include <entt.hpp>
#include <glm/vec3.hpp>

#include "CollisionEvent.h"
#include "WallCollisionEvent.h"

class PhysicsSystem
{

    static constexpr glm::vec3 GravityAcceleration{0, -9.81f, 0};

  public:
    PhysicsSystem(entt::registry &reg, entt::dispatcher &dispatcher);

    void update(float dt);
    void onCollision(CollisionEvent &event);
    void onWallCollision(WallCollisionEvent &event);
    void subscribe(entt::dispatcher &dispatcher);

  private:
    entt::registry &m_Registry;
    entt::dispatcher &m_Dispatcher;
};

#pragma once

#include <entt.hpp>

#include "CircleColliderComponent.h"
#include "TransformComponent.h"

struct OBBColliderComponent;

class CollisionSystem
{

  public:
    CollisionSystem(entt::registry &registry, entt::dispatcher &dispatcher);

    bool checkCollision(const CircleColliderComponent &colliderA,
                        const CircleColliderComponent &colliderB,
                        const TransformComponent &transformA, const TransformComponent &transformB);

    void CheckCollisions();
    void CheckWallCollisions();
    void CheckOBBCollisions();
    void SyncOBBCollider();
private:
    bool TestOBBCollision(const OBBColliderComponent& A, const OBBColliderComponent& B);
  private:
    entt::registry &m_Registry;
    entt::dispatcher &m_Dispatcher;
};

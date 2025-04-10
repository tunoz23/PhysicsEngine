
#include "CollisionSystem.h"

#include "CollisionEvent.h"
#include "RenderSystem.h"
#include "TransformComponent.h"
#include "WallCollisionEvent.h"
#include <glm/geometric.hpp>

CollisionSystem::CollisionSystem(entt::registry &registry, entt::dispatcher &dispatcher)
    : m_Registry(registry), m_Dispatcher(dispatcher)
{
}

bool CollisionSystem::checkCollision(const CircleColliderComponent &colliderA,
                                     const CircleColliderComponent &colliderB,
                                     const TransformComponent &transformA,
                                     const TransformComponent &transformB)
{
    // Calculate the distance between the centers of the two colliders
    float distance = glm::length(transformA.position - transformB.position);
    // Check if the distance is less than the sum of the radii
    return distance < (colliderA.radius + colliderB.radius);
}

void CollisionSystem::CheckCollisions()
{
    auto view = m_Registry.view<CircleColliderComponent, TransformComponent>();
    for (auto entityA : view)
    {
        auto &colliderA = view.get<CircleColliderComponent>(entityA);
        auto &transformA = view.get<TransformComponent>(entityA);
        for (auto entityB : view)
        {
            if (entityA == entityB)
                continue; // Skip self-collision
            auto &colliderB = view.get<CircleColliderComponent>(entityB);
            auto &transformB = view.get<TransformComponent>(entityB);
            if (checkCollision(colliderA, colliderB, transformA, transformB))
            {
                // Handle collision resolution here
                glm::vec3 collisionNormal =
                    glm::normalize(transformB.position - transformA.position);
                float overlap = (colliderA.radius + colliderB.radius) -
                                glm::length(transformA.position - transformB.position);

                m_Dispatcher.trigger<CollisionEvent>({entityA, entityB, overlap, collisionNormal});
                ;
            }
        }
    }
}
void CollisionSystem::CheckWallCollisions()
{
    float aspectRatio = RenderSystem::aspectRatio;

    float windowLeft = RenderSystem::windowLeft * aspectRatio;
    float windowRight = RenderSystem::windowRight * aspectRatio;
    float windowBottom = RenderSystem::windowBottom;
    float windowTop = RenderSystem::windowTop;

    auto view = m_Registry.view<CircleColliderComponent, TransformComponent>();
    for (auto entity : view)
    {
        auto &collider = view.get<CircleColliderComponent>(entity);
        auto &transform = view.get<TransformComponent>(entity);

        // Left & right
        if (transform.position.x - collider.radius < windowLeft)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::LEFT});

        else if (transform.position.x + collider.radius > windowRight)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::RIGHT});

        // Top & bottom
        else if (transform.position.y - collider.radius < windowBottom)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::BOTTOM});

        else if (transform.position.y + collider.radius > windowTop)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::TOP});
    }
}

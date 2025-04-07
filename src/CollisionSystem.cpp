
#include "CollisionSystem.h"

#include "CollisionEvent.h"
#include "TransformComponent.h"
#include "glm/geometric.hpp"

CollisionSystem::CollisionSystem(entt::registry& registry, entt::dispatcher& dispatcher)
	: m_Registry(registry), m_Dispatcher(dispatcher)
{
	
}

bool CollisionSystem::checkCollision(const CircleColliderComponent& colliderA, const CircleColliderComponent& colliderB,
                                     const TransformComponent& transformA, const TransformComponent& transformB)
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
		auto& colliderA = view.get<CircleColliderComponent>(entityA);
		auto& transformA = view.get<TransformComponent>(entityA);
		for (auto entityB : view)
		{
			if (entityA == entityB) continue; // Skip self-collision
			auto& colliderB = view.get<CircleColliderComponent>(entityB);
			auto& transformB = view.get<TransformComponent>(entityB);
			if (checkCollision(colliderA, colliderB, transformA, transformB))
			{
				// Handle collision resolution here
				glm::vec3 collisionNormal = glm::normalize(transformB.position - transformA.position);
				float overlap = (colliderA.radius + colliderB.radius) - glm::length(transformA.position - transformB.position);

				m_Dispatcher.trigger<CollisionEvent>({entityA, entityB, overlap, collisionNormal});
				;
			}
		}
	}
}

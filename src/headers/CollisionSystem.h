#pragma once

#include <entt.hpp>

#include "CircleColliderComponent.h"
#include "TransformComponent.h"

class CollisionSystem
{


public:

	static bool checkCollision(
		const CircleColliderComponent& colliderA, const CircleColliderComponent& colliderB,
		const TransformComponent& transformA,     const TransformComponent& transformB);

	static void solveCollisions(entt::registry& registry, entt::dispatcher& dispatcher);


};

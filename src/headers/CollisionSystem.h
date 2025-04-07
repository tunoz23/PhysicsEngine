#pragma once

#include <entt.hpp>

#include "CircleColliderComponent.h"
#include "TransformComponent.h"

class CollisionSystem
{

public:

	CollisionSystem(entt::registry& registry, entt::dispatcher& dispatcher);


	bool checkCollision(
		const CircleColliderComponent& colliderA, const CircleColliderComponent& colliderB,
		const TransformComponent& transformA,     const TransformComponent& transformB);

	void CheckCollisions();
	void CheckWallCollisions();


private:
	entt::registry& m_Registry;
	entt::dispatcher& m_Dispatcher;

};

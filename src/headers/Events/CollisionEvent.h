
#pragma once
#include<glm/glm.hpp>
#include <entt.hpp>
struct CollisionEvent
{
	entt::entity entityA;
	entt::entity entityB;
	float penetrationDepth; // The depth of penetration between the two colliders
	glm::vec3 collisionNormal; // The normal vector at the point of collision
	CollisionEvent(entt::entity entityA, entt::entity entityB, float penetrationDepth, glm::vec3 collisionNormal)
		: entityA(entityA), entityB(entityB), penetrationDepth(penetrationDepth), collisionNormal(collisionNormal) {
	}
};
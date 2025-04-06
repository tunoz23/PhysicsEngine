//
// Created by Tuna Öztürk on 30.03.2025.
//

#pragma once
#include <entt.hpp>

#include "glm/vec3.hpp"
#include <CollisionEvent.h>


class PhysicsSystem
{
private:
    entt::registry& m_Registry;

    static constexpr glm::vec3 GravityAcceleration{0,-9.81f,0};
public:
    PhysicsSystem(entt::registry& reg);

     void update(entt::registry& registry,float dt);
     void onCollision(CollisionEvent& event);
     void subscribe(entt::dispatcher& dispatcher);
	
};



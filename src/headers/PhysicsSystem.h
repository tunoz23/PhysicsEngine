//
// Created by Tuna Öztürk on 30.03.2025.
//

#pragma once
#include <entt.hpp>

#include "glm/vec3.hpp"


class PhysicsSystem
{
private:
    static constexpr glm::vec3 GravityAcceleration{0,-9.81f,0};
public:
    PhysicsSystem() = delete;
    PhysicsSystem(const PhysicsSystem& rhs) = delete;
    PhysicsSystem(PhysicsSystem&& rhs) = delete;
    PhysicsSystem& operator=(const PhysicsSystem& rhs) = delete;
    PhysicsSystem& operator=(PhysicsSystem&& rhs) = delete;
    ~PhysicsSystem() = delete;

    static void update(entt::registry& registry,float dt);

};



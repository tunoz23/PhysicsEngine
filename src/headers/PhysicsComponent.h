//
// Created by Tuna Öztürk on 30.03.2025.
//

#pragma once
#include "glm/vec3.hpp"

struct PhysicsComponent {
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 force;
    float mass;

    PhysicsComponent(glm::vec3 velocity, glm::vec3 acceleration, glm::vec3 force, float mass)
        :velocity(velocity), acceleration(acceleration), force(force), mass(mass) {}

    PhysicsComponent(PhysicsComponent const& other)
        :velocity(other.velocity), acceleration(other.acceleration),force(other.force), mass(other.mass) {}




};

//
// Created by Tuna Öztürk on 30.03.2025.
//

#pragma once
#include <glm/vec3.hpp>

struct PhysicsComponent
{
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 force;
    float restitution; // 0 = inelastic, 1 = perfectly elastic
    float mass;
    /*
     * @brief Constructs a PhysicsComponent with initial physical properties.
     *
     * @param velocity     Initial velocity of the object.
     * @param acceleration Initial acceleration of the object.
     * @param force        Force currently applied to the object.
     * @param restitution  Bounciness factor (0 = inelastic, 1 = perfectly
     * elastic).
     * @param mass         Mass of the object.
     */
    PhysicsComponent(glm::vec3 velocity, glm::vec3 acceleration, glm::vec3 force, float restitution,
                     float mass)
        : velocity(velocity), acceleration(acceleration), force(force), restitution(restitution),
          mass(mass)
    {
    }

    PhysicsComponent(PhysicsComponent const &other)
        : velocity(other.velocity), acceleration(other.acceleration), force(other.force),
          restitution(other.restitution), mass(other.mass)
    {
    }
};

#pragma once
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

struct PhysicsComponent
{
    // Linear
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 force;

    // Angular
    glm::vec3 angularVelocity = glm::vec3(0.0f);     // ω
    glm::vec3 torque = glm::vec3(0.0f);              // τ
    glm::mat3 inertiaTensor = glm::mat3(1.0f);       // I
    glm::mat3 inverseInertiaTensor = glm::mat3(1.0f); // I⁻¹

    // Material
    float restitution; // 0 = inelastic, 1 = perfectly elastic
    float mass;
    bool isStatic;

    PhysicsComponent(glm::vec3 velocity, glm::vec3 acceleration, glm::vec3 force,
                     float restitution, float mass, bool isStatic)
        : velocity(velocity), acceleration(acceleration), force(force),
          restitution(restitution), mass(mass), isStatic(isStatic)
    {
        // You can assign the inertia tensor for a cube here if you know its size
        if (!isStatic) {
            float s = 1.0f; // Replace with actual cube half-extent if needed
            float I = (1.0f / 6.0f) * mass * s * s;
            inertiaTensor = glm::mat3(
                glm::vec3(I, 0, 0),
                glm::vec3(0, I, 0),
                glm::vec3(0, 0, I)
            );
            inverseInertiaTensor = glm::inverse(inertiaTensor);
        }
    }

    PhysicsComponent(PhysicsComponent const &other)
        : velocity(other.velocity), acceleration(other.acceleration), force(other.force),
          angularVelocity(other.angularVelocity), torque(other.torque),
          inertiaTensor(other.inertiaTensor), inverseInertiaTensor(other.inverseInertiaTensor),
          restitution(other.restitution), mass(other.mass), isStatic(other.isStatic)
    {
    }
};

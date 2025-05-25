//
// Created by Tuna Öztürk on 30.03.2025.
//
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "PhysicsSystem.h"
#include <glm/gtx/string_cast.hpp>
#include "CircleColliderComponent.h"
#include "OBBColliderComponent.h"
#include "OBBCollisionEvent.h"
#include "PhysicsComponent.h"
#include "RenderSystem.h"
#include "TransformComponent.h"

PhysicsSystem::PhysicsSystem(entt::registry &reg, entt::dispatcher &dispatcher)
    : m_Registry(reg), m_Dispatcher(dispatcher)
{
    // subscribe(m_Dispatcher);
}

void PhysicsSystem::update(float dt)
{
    auto view = m_Registry.view<PhysicsComponent, TransformComponent>();

    for (auto entity : view)
    {
        auto &pc = view.get<PhysicsComponent>(entity);
        auto &tc = view.get<TransformComponent>(entity);

        if (pc.isStatic)
            continue;

        // Apply linear motion
        glm::vec3 accel = (pc.mass != 0.0f) ? (pc.acceleration + GravityAcceleration) : pc.acceleration;
        pc.velocity += accel * dt;
        tc.position += pc.velocity * dt;

        // Apply angular motion
        //pc.angularVelocity += pc.inverseInertiaTensor * pc.torque * dt;
        // Assume you apply angular velocity to transform orientation here
        // (e.g., tc.rotation = glm::quat(...) or tc.rotation += ...)
        // Convert angular velocity (rad/s) to degrees and integrate over time
        tc.rotation += glm::degrees(pc.angularVelocity * dt);
        //std::cout << (int)entity << << "\n";
        // Reset torque for next frame
        //pc.torque = glm::vec3(0.0f);
    }
}

void PhysicsSystem::onCollision(CollisionEvent &event)
{
    auto &physA = m_Registry.get<PhysicsComponent>(event.entityA);
    auto &physB = m_Registry.get<PhysicsComponent>(event.entityB);

    // If both are static, nothing to do
    if (physA.isStatic && physB.isStatic)
        return;

    // Compute relative velocity along collision normal
    glm::vec3 relVel = physB.velocity - physA.velocity;
    float velAlongNormal = glm::dot(relVel, event.collisionNormal);

    // Already separating?
    if (velAlongNormal > 0)
        return;

    // Compute impulse scalar
    float e = std::min(physA.restitution, physB.restitution);
    float j = -(1 + e) * velAlongNormal;

    // Denominator: for a static body, treat 1/mass = 0
    float invMassA = physA.isStatic ? 0.0f : 1.0f / physA.mass;
    float invMassB = physB.isStatic ? 0.0f : 1.0f / physB.mass;
    j /= (invMassA + invMassB);

    glm::vec3 impulse = j * event.collisionNormal;

    // Apply impulse only to non–static bodies
    if (!physA.isStatic)
        physA.velocity -= impulse * invMassA;
    if (!physB.isStatic)
        physB.velocity += impulse * invMassB;
}

void PhysicsSystem::OnOBBCollision(const OBBCollisionEvent &event)
{
    auto &pcA = m_Registry.get<PhysicsComponent>(event.a);
    auto &pcB = m_Registry.get<PhysicsComponent>(event.b);
    if (pcA.isStatic && pcB.isStatic)
        return;

    auto &obbA = m_Registry.get<OBBColliderComponent>(event.a);
    auto &obbB = m_Registry.get<OBBColliderComponent>(event.b);

    // Use proper collision normal from SAT (replace this with event.collisionNormal if available)
    glm::vec3 normal = glm::normalize(obbB.center - obbA.center);

    // Approximate contact point as midpoint
    glm::vec3 contactPoint = (obbA.center + obbB.center) * 0.5f;

    // Lever arms
    glm::vec3 rA = contactPoint - obbA.center;
    glm::vec3 rB = contactPoint - obbB.center;

    // Relative velocity at contact point
    glm::vec3 vA = pcA.velocity + glm::cross(pcA.angularVelocity, rA);
    glm::vec3 vB = pcB.velocity + glm::cross(pcB.angularVelocity, rB);
    glm::vec3 relVel = vB - vA;

    float velAlongNormal = glm::dot(relVel, normal);
    if (velAlongNormal > 0.0f)
        return; // separating

    float e = std::min(pcA.restitution, pcB.restitution);
    float invMassA = pcA.isStatic ? 0.0f : 1.0f / pcA.mass;
    float invMassB = pcB.isStatic ? 0.0f : 1.0f / pcB.mass;

    // Calculate rotational inertia terms
    glm::vec3 raCrossN = glm::cross(rA, normal);
    glm::vec3 rbCrossN = glm::cross(rB, normal);
    float angularTermA = pcA.isStatic ? 0.0f : glm::dot(normal, glm::cross(pcA.inverseInertiaTensor * raCrossN, rA));
    float angularTermB = pcB.isStatic ? 0.0f : glm::dot(normal, glm::cross(pcB.inverseInertiaTensor * rbCrossN, rB));

    float denom = invMassA + invMassB + angularTermA + angularTermB;
    if (denom == 0.0f)
        return;

    float j = -(1.0f + e) * velAlongNormal / denom;
    glm::vec3 impulse = j * normal;

    // Apply linear impulse
    if (!pcA.isStatic) pcA.velocity -= impulse * invMassA;
    if (!pcB.isStatic) pcB.velocity += impulse * invMassB;

    // Apply angular impulse
    if (!pcA.isStatic)
        pcA.angularVelocity -= pcA.inverseInertiaTensor * glm::cross(rA, impulse);
    if (!pcB.isStatic)
        pcB.angularVelocity += pcB.inverseInertiaTensor * glm::cross(rB, impulse);
       std::cout <<  glm::to_string( pcA.angularVelocity) << "\n";
       std::cout <<  glm::to_string( pcB.angularVelocity) << "\n";
    //std::cout << "Resolved OBB collision between " << int(event.a) << " and " << int(event.b) << std::endl;
}


void PhysicsSystem::subscribe(entt::dispatcher &dispatcher)
{
    dispatcher.sink<CollisionEvent>().connect<&PhysicsSystem::onCollision>(this);
    dispatcher.sink<OBBCollisionEvent>().connect<&PhysicsSystem::OnOBBCollision>(this);
}

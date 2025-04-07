//
// Created by Tuna Öztürk on 30.03.2025.
//

#include "PhysicsSystem.h"

#include "CircleColliderComponent.h"
#include "PhysicsComponent.h"
#include "RenderSystem.h"
#include "TransformComponent.h"


PhysicsSystem::PhysicsSystem(entt::registry& reg, entt::dispatcher& dispatcher)
	:m_Registry(reg), m_Dispatcher(dispatcher)
{
    //subscribe(m_Dispatcher);
}

void PhysicsSystem::update(float dt)
{
    auto view = m_Registry.view<PhysicsComponent, TransformComponent>();

    for (auto entity : view)
    {
        auto& physicsComponent = view.get<PhysicsComponent>(entity);
        auto& transformComponent = view.get<TransformComponent>(entity);


        if (physicsComponent.mass != 0.0f)
            physicsComponent.velocity += (physicsComponent.acceleration + PhysicsSystem::GravityAcceleration )* dt;

        else
            physicsComponent.velocity += physicsComponent.acceleration  * dt;

        
        transformComponent.position += physicsComponent.velocity * dt;


    }

}

void PhysicsSystem::onCollision(CollisionEvent& event)
{

    //TO DO: IT DOESNT WORKKKKKKKKKK

    auto& physicsA =  m_Registry.get<PhysicsComponent>(event.entityA);
    auto& physicsB = m_Registry.get<PhysicsComponent>(event.entityB);
    // Calculate the new velocities after collision
    glm::vec3 relativeVelocity = physicsB.velocity - physicsA.velocity;
    float velocityAlongNormal = glm::dot(relativeVelocity, event.collisionNormal);
    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0)
        return;
    // Calculate restitution
    float e = std::min(physicsA.restitution, physicsB.restitution);
    // Calculate impulse scalar
    float j = -(1 + e) * velocityAlongNormal;
    j /= (1 / physicsA.mass + 1 / physicsB.mass);
    // Apply impulse
    glm::vec3 impulse = j * event.collisionNormal;
    physicsA.velocity -= impulse / physicsA.mass;
    physicsB.velocity += impulse / physicsB.mass;

}

void PhysicsSystem::onWallCollision(WallCollisionEvent& event)
{
    float aspectRatio = RenderSystem::aspectRatio;

    float windowLeft = RenderSystem::windowLeft * aspectRatio;
    float windowRight = RenderSystem::windowRight * aspectRatio;
    float windowBottom = RenderSystem::windowBottom;
    float windowTop = RenderSystem::windowTop;

   // auto [tc,pc,ccc]
    //= m_Registry.get<TransformComponent,PhysicsComponent,CircleColliderComponent>(event.entity);
    std::cout << "Has collidied" << (int)event.entity << "\n";
    auto& tc = m_Registry.get<TransformComponent>(event.entity);
    auto& pc = m_Registry.get<PhysicsComponent>(event.entity);
    auto& ccc = m_Registry.get<CircleColliderComponent>(event.entity);
    switch (event.wall)
    {
        case WALL::LEFT:
            tc.position.x = windowLeft + ccc.radius;
            pc.velocity.x *= -pc.restitution;
            break;
        case WALL::RIGHT:
            tc.position.x = windowRight - ccc.radius;
            pc.velocity.x *= -pc.restitution;
            break;
        case WALL::BOTTOM:
            tc.position.y = windowBottom + ccc.radius;
            pc.velocity.y *= -pc.restitution;
            break;
        case WALL::TOP:
            tc.position.y = windowTop - ccc.radius;
            pc.velocity.y *= -pc.restitution;
            break;
        default:
            break;
    }
}

void PhysicsSystem::subscribe(entt::dispatcher& dispatcher)
{
    dispatcher.sink<CollisionEvent>().connect<&PhysicsSystem::onCollision>(this);
    dispatcher.sink<WallCollisionEvent>().connect<&PhysicsSystem::onWallCollision>(this);

}


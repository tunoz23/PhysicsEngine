//
// Created by Tuna Öztürk on 30.03.2025.
//

#include "PhysicsSystem.h"

#include "PhysicsComponent.h"
#include "TransformComponent.h"

void PhysicsSystem::update(entt::registry& registry,float dt)
{
    auto view = registry.view<PhysicsComponent, TransformComponent>();

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

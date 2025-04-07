//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <entt.hpp>
#include <Shader.h>
#include <RenderSystem.h>

#include "CollisionSystem.h"
#include "PhysicsSystem.h"


class Scene {
public:

    RenderSystem renderSystem;
    PhysicsSystem physicsSystem;
	CollisionSystem collisionSystem;

    Scene(Shader shader);
    ~Scene() = default;

    void main(double dt);
private:
    entt::registry m_Registry;
    entt::dispatcher m_Dispatcher;

};

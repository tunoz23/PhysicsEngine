//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <entt.hpp>
#include <Shader.h>
#include <RenderSystem.h>

#include "PhysicsSystem.h"


class Scene {
public:
    entt::dispatcher dispatcher;

    RenderSystem renderSystem;
    PhysicsSystem physicsSystem;
    Scene(Shader shader);
    ~Scene() = default;

    void main(double dt);
private:
    entt::registry m_Registry;
};

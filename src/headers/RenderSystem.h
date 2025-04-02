//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <entt.hpp>

#include "MeshComponent.h"
#include "Shader.h"

class RenderSystem {

    Shader m_Shader;


public:
    RenderSystem(Shader shader);
    ~RenderSystem() = default;

    void render(const MeshComponent& meshComponent) const;
    void render(entt::registry& registry) const;
    static void initializeMesh(entt::registry& registry);
};

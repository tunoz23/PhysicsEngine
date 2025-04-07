//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <entt.hpp>

#include "MeshComponent.h"
#include "Shader.h"

class RenderSystem {


public:
    static float windowLeft;
    static float windowRight;
    static float windowBottom;
    static float windowTop;
    static float aspectRatio;

public:

    RenderSystem(Shader shader, entt::registry& registry);
    ~RenderSystem() = default;

    void render(const MeshComponent& meshComponent) const;
    void render() const;

    
    static void initializeMesh(entt::registry& registry);
private:
    Shader m_Shader;
	entt::registry& m_Registry;

};

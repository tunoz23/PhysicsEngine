//
// Created by Tuna Öztürk on 7.04.2025.
//

#pragma once
#include <entt.hpp>

enum class WALL {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

struct WallCollisionEvent {
    entt::entity entity;
    WALL wall;
};
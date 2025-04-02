//
// Created by Tuna Öztürk on 30.03.2025.
//
#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
struct TransformComponent {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f}; // in degrees
    glm::vec3 scale{1.0f, 1.0f, 1.0f};


    TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale) {}

    TransformComponent(TransformComponent const& other)
        : position(other.position), rotation(other.rotation), scale(other.scale) {}

    TransformComponent(TransformComponent const&& other) noexcept
        : position(other.position), rotation(other.rotation), scale(other.scale) {}


    // Compute the transformation matrix from position, rotation, and scale.
    glm::mat4 getMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        // Translate
        model = glm::translate(model, position);
        // Rotate (assuming rotation order: Z, Y, X)
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        // Scale
        model = glm::scale(model, scale);

        //std::cout << glm::to_string(model) << "\n";
        return model;
    }
};
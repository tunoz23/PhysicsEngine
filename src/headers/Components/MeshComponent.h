//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <glad/glad.h>
#include <vector>

struct MeshComponent
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int vao, vbo, ebo;

    /*
    @brief initializes Mesh component using vertices and indices.
    @param vertices reference to vertices vector.
    @param indices reference to indices vector.

    */
    MeshComponent(const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
        : vertices(vertices), indices(indices)
    {
    }
};

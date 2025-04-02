//
// Created by Tuna Öztürk on 29.03.2025.
//

#pragma once
#include <utility>
#include <vector>
#include <glad/glad.h>



struct MeshComponent
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int vao, vbo, ebo;

    MeshComponent(const std::vector<float>& vertices,const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) {}
};


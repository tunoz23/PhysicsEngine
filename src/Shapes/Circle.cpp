//
// Created by Tuna Öztürk on 1.04.2025.
//

#include "Circle.h"
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>

#include <cstddef>
#include <vector>

std::vector<float> generateCircleVertices(int N)
{
    std::vector<float> vertices;
    // Center vertex
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    /*********
     *  {0,0,0}
     *  {1,0,0}
     *
     *
     *
     *
     *
     *********/
    for (std::size_t i = 0; i < N; ++i)
    {
        float angle = static_cast<float>(i * 2.0f * glm::pi<float>() / N);

        vertices.push_back(glm::cos(angle));
        vertices.push_back(glm::sin(angle));
        vertices.push_back(0.0f);
    }

    return vertices;
}

std::vector<unsigned int> generateCircleIndices(int N)
{
    std::vector<unsigned int> indices(N * 3);

    for (std::size_t i = 0; i < N; ++i)
    {
        indices[3 * i] = 0;                   // Center vertex
        indices[3 * i + 1] = i + 1;           // Current outer vertex
        indices[3 * i + 2] = (i + 1) % N + 1; // Next outer vertex
    }
    return indices;
}

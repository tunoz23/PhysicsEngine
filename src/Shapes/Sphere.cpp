// sphere.cpp
#include "Sphere.h"
#include <stdexcept>
#include <cmath>

// Use acos(-1) for PI
#ifndef M_PI
    // Define PI using acos, which is a portable way
const float PI = std::acos(-1.0f);
#else
const float PI = M_PI;
#endif

std::vector<float> generateUVSphereVertices(float radius,
    unsigned int rings,
    unsigned int segments)
{
    if (radius <= 0.0f)       throw std::invalid_argument("radius must be > 0");
    if (rings < 1)          throw std::invalid_argument("rings must be >= 1");
    if (segments < 3)          throw std::invalid_argument("segments must be >= 3");

    // Each vertex is only x,y,z
    std::vector<float> positions;
    positions.reserve((rings + 1) * (segments + 1) * 3);

    for (unsigned int r = 0; r <= rings; ++r) {
        float phi = float(r) * PI / float(rings);            // 0→π
        float y = radius * std::cos(phi);                  // Y coordinate
        float sinPhi = std::sin(phi);

        for (unsigned int s = 0; s <= segments; ++s) {
            float theta = float(s) * 2.0f * PI / float(segments);  // 0→2π
            float x = radius * sinPhi * std::cos(theta);
            float z = radius * sinPhi * std::sin(theta);

            positions.push_back(x);
            positions.push_back(y);
            positions.push_back(z);
        }
    }
    return positions;
}

std::vector<unsigned int> generateUVSphereIndices(unsigned int rings,
    unsigned int segments)
{
    if (rings < 1) throw std::invalid_argument("rings must be >= 1");
    if (segments < 3) throw std::invalid_argument("segments must be >= 3");

    std::vector<unsigned int> indices;
    indices.reserve(rings * segments * 6);

    // (segments+1) verts per ring
    for (unsigned int r = 0; r < rings; ++r) {
        unsigned int ringStart = r * (segments + 1);
        unsigned int nextStart = (r + 1) * (segments + 1);

        for (unsigned int s = 0; s < segments; ++s) {
            // quad corners
            unsigned int topLeft = ringStart + s;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = nextStart + s;
            unsigned int bottomRight = bottomLeft + 1;

            // first triangle
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            // second triangle
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    return indices;
}

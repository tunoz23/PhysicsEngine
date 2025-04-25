#include <vector>

std::vector<float> generateRectangleVertices(float leftx, float lefty, float leftz,
                                             float rightx, float righty, float rightz)
{
    // Vertices in counter-clockwise order: top-left, top-right, bottom-right, bottom-left
    std::vector<float> vertices = {
        leftx,  lefty,  leftz,  // 0: top-left
        rightx, lefty,  leftz,  // 1: top-right
        rightx, righty, rightz, // 2: bottom-right
        leftx,  righty, rightz  // 3: bottom-left
    };
    return vertices;
}

std::vector<unsigned int> generateRectangleIndices()
{
    // Two triangles: (0, 1, 2) and (2, 3, 0)
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    return indices;
}

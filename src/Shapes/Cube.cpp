// 8 positions at ±0.5
#include "Cube.h"

std::vector<float> generateCubeVertices()
{
    float h = 0.5f;
    return {
        -h, -h, -h,  // 0
         h, -h, -h,  // 1
         h,  h, -h,  // 2
        -h,  h, -h,  // 3
        -h, -h,  h,  // 4
         h, -h,  h,  // 5
         h,  h,  h,  // 6
        -h,  h,  h   // 7
    };
}

std::vector<unsigned int> generateCubeIndices()
{
    return {
        // front face (z = +0.5): 4,5,6, 6,7,4
         4,5,6,  6,7,4,
        // back  face (z = -0.5): 0,1,2, 2,3,0
         0,1,2,  2,3,0,
        // left  face (x = -0.5): 0,4,7, 7,3,0
         0,4,7,  7,3,0,
        // right face (x = +0.5): 1,5,6, 6,2,1
         1,5,6,  6,2,1,
        // top   face (y = +0.5): 3,2,6, 6,7,3
         3,2,6,  6,7,3,
        // bottom face (y = -0.5): 0,1,5, 5,4,0
         0,1,5,  5,4,0
    };
}

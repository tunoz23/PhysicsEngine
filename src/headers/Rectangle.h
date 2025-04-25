#pragma once
#include <vector>


/*
 * @brief Creates vertices vector for a rectangle.
 *
 * @param leftx      Top left x coordinates.
 * @param lefty Initial Top left y coordinates.
 * @param leftz        Top left z coordinates.
 * @param rightx
 * @param rightx bottom right x coordinates.
 * @param righty bottom right y coordinates.
 * @param rightz bottom right z coordinates.
 */
std::vector<float> generateRectangleVertices(float leftx, float lefty,float leftz, float rightx, float righty, float rightz);

/*
 * @brief Generates index buffer for two triangles forming a rectangle (using 4 vertices).
 * @return std::vector<float> Indices for a rectangle drawn using GL_TRIANGLES.
 */
std::vector<unsigned int> generateRectangleIndices();

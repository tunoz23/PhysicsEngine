// icosphere.h
#pragma once

#include <vector>

// Generates an icosphere mesh by subdividing an icosahedron.
// radius: sphere radius
// subdivisions: number of recursive subdivisions (>= 0)
// Returns interleaved vertex attributes [x, y, z, nx, ny, nz].
std::vector<float> generateUVSphereVertices(float radius, unsigned int rings, unsigned int segments);

// Generates triangle indices (GL_TRIANGLES) for an icosphere of given subdivisions.
std::vector<unsigned int> generateUVSphereIndices(unsigned int rings, unsigned int segments);

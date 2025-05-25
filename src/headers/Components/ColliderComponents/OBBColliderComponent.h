#pragma once

#include "glm/glm.hpp"

struct OBBColliderComponent {
    glm::vec3 center;        // World-space center of the box (usually set from Transform)
    glm::vec3 axes[3];       // Local orientation axes (should be normalized)
    glm::vec3 halfSizes;     // Actual half-size in world-space after scaling (computed from baseHalfSize * scale)
    glm::vec3 baseHalfSize;  // Original model-space half-size before scaling

    // Constructor
    OBBColliderComponent(
        const glm::vec3& inCenter,
        const std::array<glm::vec3, 3>& inAxes,
        const glm::vec3& inHalfSizes,
        const glm::vec3& inBaseHalfSize
    )
        : center(inCenter),
          halfSizes(inHalfSizes),
          baseHalfSize(inBaseHalfSize)
    {
        axes[0] = glm::normalize(inAxes[0]);
        axes[1] = glm::normalize(inAxes[1]);
        axes[2] = glm::normalize(inAxes[2]);
    }
};

#include <glm/glm.hpp>

struct OBBColliderComponent
{
    glm::vec2 halfExtents;
    float rotation; // in radians

    constexpr OBBColliderComponent() = default;
    constexpr OBBColliderComponent(glm::vec2 p_halfExtends, float p_rotation)
        : halfExtents(p_halfExtends), rotation(p_rotation)
    {
    }

};

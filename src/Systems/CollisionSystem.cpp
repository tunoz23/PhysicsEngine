
#include "CollisionSystem.h"

#include "CollisionEvent.h"
#include "OBBColliderComponent.h"
#include "OBBCollisionEvent.h"
#include "RenderSystem.h"
#include "TransformComponent.h"
#include "WallCollisionEvent.h"
#include "glm/gtc/quaternion.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/geometric.hpp>

CollisionSystem::CollisionSystem(entt::registry &registry, entt::dispatcher &dispatcher)
    : m_Registry(registry), m_Dispatcher(dispatcher)
{
}

bool CollisionSystem::checkCollision(const CircleColliderComponent &colliderA, const CircleColliderComponent &colliderB,
                                     const TransformComponent &transformA, const TransformComponent &transformB)
{
    // Calculate the distance between the centers of the two colliders
    float distance = glm::length(transformA.position - transformB.position);
    // Check if the distance is less than the sum of the radii
    return distance < (colliderA.radius + colliderB.radius);
}

void CollisionSystem::CheckCollisions()
{
    auto view = m_Registry.view<CircleColliderComponent, TransformComponent>();
    for (auto entityA : view)
    {
        auto &colliderA = view.get<CircleColliderComponent>(entityA);
        auto &transformA = view.get<TransformComponent>(entityA);
        for (auto entityB : view)
        {
            if (entityA == entityB)
                continue; // Skip self-collision
            auto &colliderB = view.get<CircleColliderComponent>(entityB);
            auto &transformB = view.get<TransformComponent>(entityB);
            if (checkCollision(colliderA, colliderB, transformA, transformB))
            {
                // Handle collision resolution here
                glm::vec3 collisionNormal = glm::normalize(transformB.position - transformA.position);
                float overlap =
                    (colliderA.radius + colliderB.radius) - glm::length(transformA.position - transformB.position);

                m_Dispatcher.trigger<CollisionEvent>({entityA, entityB, overlap, collisionNormal});
                ;
            }
        }
    }
}
void CollisionSystem::CheckWallCollisions()
{
    float aspectRatio = RenderSystem::aspectRatio;

    float windowLeft = RenderSystem::windowLeft * aspectRatio;
    float windowRight = RenderSystem::windowRight * aspectRatio;
    float windowBottom = RenderSystem::windowBottom;
    float windowTop = RenderSystem::windowTop;

    auto view = m_Registry.view<CircleColliderComponent, TransformComponent>();
    for (auto entity : view)
    {
        auto &collider = view.get<CircleColliderComponent>(entity);
        auto &transform = view.get<TransformComponent>(entity);

        // Left & right
        if (transform.position.x - collider.radius < windowLeft)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::LEFT});

        else if (transform.position.x + collider.radius > windowRight)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::RIGHT});

        // Top & bottom
        else if (transform.position.y - collider.radius < windowBottom)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::BOTTOM});

        else if (transform.position.y + collider.radius > windowTop)
            m_Dispatcher.trigger<WallCollisionEvent>({entity, WALL::TOP});
    }
}

bool testOBBCollision(const OBBColliderComponent &A, const OBBColliderComponent &B) {
    const float EPSILON = 1e-5f;
    glm::mat3 R;
    glm::mat3 AbsR;

    // Compute rotation matrix R[i][j] = dot(A.axes[i], B.axes[j])
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            R[i][j] = glm::dot(A.axes[i], B.axes[j]);

    // Compute translation t in A's frame
    glm::vec3 t = B.center - A.center;
    t = glm::vec3(glm::dot(t, A.axes[0]),
                  glm::dot(t, A.axes[1]),
                  glm::dot(t, A.axes[2]));

    // Compute AbsR = |R| + EPSILON
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            AbsR[i][j] = std::abs(R[i][j]) + EPSILON;

    float ra, rb;

    // Test axes A0, A1, A2
    for (int i = 0; i < 3; ++i) {
        ra = A.halfSizes[i];
        rb = B.halfSizes[0] * AbsR[i][0]
           + B.halfSizes[1] * AbsR[i][1]
           + B.halfSizes[2] * AbsR[i][2];
        if (std::abs(t[i]) > ra + rb) return false;
    }

    // Test axes B0, B1, B2
    for (int i = 0; i < 3; ++i) {
        ra = A.halfSizes[0] * AbsR[0][i]
           + A.halfSizes[1] * AbsR[1][i]
           + A.halfSizes[2] * AbsR[2][i];
        rb = B.halfSizes[i];
        float proj = std::abs(t.x * R[0][i] + t.y * R[1][i] + t.z * R[2][i]);
        if (proj > ra + rb) return false;
    }

    // Test cross products
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            ra = A.halfSizes[(i+1)%3] * AbsR[(i+2)%3][j]
               + A.halfSizes[(i+2)%3] * AbsR[(i+1)%3][j];
            rb = B.halfSizes[(j+1)%3] * AbsR[i][(j+2)%3]
               + B.halfSizes[(j+2)%3] * AbsR[i][(j+1)%3];
            float val = std::abs(t[(i+2)%3] * R[(i+1)%3][j]
                               - t[(i+1)%3] * R[(i+2)%3][j]);
            if (val > ra + rb) return false;
        }

    return true;
}
void CollisionSystem::SyncOBBCollider() {
    auto view = m_Registry.view<TransformComponent, OBBColliderComponent>();

    for (auto entity : view) {
        auto &tc  = view.get<TransformComponent>(entity);
        auto &obb = view.get<OBBColliderComponent>(entity);

        // 1) Update center
        obb.center = tc.position;

        // 2) Build rotation matrix from Euler degrees
        glm::vec3 rad = glm::radians(tc.rotation);
        glm::quat q    = glm::quat(rad);           // (pitch,yaw,roll) in radians
        glm::mat3 rotM = glm::mat3_cast(q);

        // 3) Update axes
        obb.axes[0] = glm::normalize(rotM[0]);
        obb.axes[1] = glm::normalize(rotM[1]);
        obb.axes[2] = glm::normalize(rotM[2]);

        // 4) Reset halfSizes from immutable base
        obb.halfSizes = obb.baseHalfSize * tc.scale;
    }
}


void CollisionSystem::CheckOBBCollisions()
{
    auto view = m_Registry.view<OBBColliderComponent>();
    std::vector<entt::entity> entities(view.begin(), view.end());
    for (size_t i = 0; i < entities.size(); ++i)
    {
        for (size_t j = i + 1; j < entities.size(); ++j)
        {
            auto eA = entities[i], eB = entities[j];
            if (testOBBCollision(m_Registry.get<OBBColliderComponent>(eA), m_Registry.get<OBBColliderComponent>(eB)))
            {
                m_Dispatcher.trigger<OBBCollisionEvent>({eA, eB});
            }
        }
    }
}

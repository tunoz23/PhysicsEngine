//
// Created by Tuna Öztürk on 29.03.2025.
//
#define GLM_ENABLE_EXPERIMENTAL

#include "headers/Scene.h"
#include <glm/gtx/string_cast.hpp>

#include "ActiveCameraData.h"
#include "CameraComponent.h"
#include "Circle.h"
#include "CircleColliderComponent.h"
#include "Cube.h"
#include "MeshComponent.h"
#include "OBBColliderComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Rectangle.h"

#include "Sphere.h"
#include "TransformComponent.h"
#include <array>

Scene::Scene(Shader p_Shader)
    : renderSystem(RenderSystem(p_Shader, m_Registry)), physicsSystem(PhysicsSystem(m_Registry, m_Dispatcher)),
      collisionSystem(CollisionSystem(m_Registry, m_Dispatcher))
{
    physicsSystem.subscribe(m_Dispatcher);

    // … inside Scene::Scene(Shader p_Shader) …

    // 1) Create the camera entity at the origin, looking toward –Z
    entt::entity cameraEntity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(cameraEntity, TransformComponent{/* position */ {0.0f, 0.0f, -50.0f},
                                                                            /* rotation */ {0.0f, 0.0f, 0.0f},
                                                                            /* scale    */ {1.0f, 1.0f, 1.0f}});
    m_Registry.emplace<CameraComponent>(
        cameraEntity, CameraComponent{.fov = 45.0f, .aspectRatio = 16.0f / 9.0f, .near = 0.1f, .far = 100.0f});

    // Debug quad at Z = -5

    entt::entity Sphere1 = m_Registry.create();
    m_Registry.emplace<MeshComponent>(Sphere1,

                                      generateUVSphereVertices(1, 8, 16), generateUVSphereIndices(8, 16));
    m_Registry.emplace<TransformComponent>(Sphere1, TransformComponent{
                                                        /*position*/ {0.0f, 0.0f, -5.0f}, // 5 units in front of camera
                                                        /*rotation*/ {0.0f, 0.0f, 0.0f},
                                                        /*scale*/ {1.0f, 1.0f, 1.0f} // big enough to fill the view
                                                    });
    m_Registry.emplace<PhysicsComponent>(
        Sphere1,

        PhysicsComponent{glm::vec3{0, 20, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.9, 1, false});
    m_Registry.emplace<CircleColliderComponent>(Sphere1, CircleColliderComponent(1));

    entt::entity Sphere2 = m_Registry.create();
    m_Registry.emplace<MeshComponent>(Sphere2,

                                      generateUVSphereVertices(1, 8, 16), generateUVSphereIndices(8, 16));
    m_Registry.emplace<TransformComponent>(Sphere2, TransformComponent{
                                                        /*position*/ {0.0f, 10.0f, -5.0f}, // 5 units in front of camera
                                                        /*rotation*/ {0.0f, 0.0f, 0.0f},
                                                        /*scale*/ {1.0f, 1.0f, 1.0f} // big enough to fill the view
                                                    });
    m_Registry.emplace<PhysicsComponent>(
        Sphere2,

        PhysicsComponent{glm::vec3{0, 0, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.9, 1, false});
    m_Registry.emplace<CircleColliderComponent>(Sphere2, CircleColliderComponent(1));

    // … then call RenderSystem::initializeMesh(m_Registry) …
    /*
    m_Registry.emplace<MeshComponent>(circleEntity, generateCircleVertices(N), generateCircleIndices(N));
    m_Registry.emplace<MeshComponent>(circleEntity2, generateCircleVertices(N), generateCircleIndices(N));

    m_Registry.emplace<TransformComponent>(
        circleEntity, TransformComponent{glm::vec3(-20.f, 0.0f, 0.f), glm::vec3(0, 0, 0), glm::vec3(1.f)});

    m_Registry.emplace<PhysicsComponent>(
        circleEntity, PhysicsComponent{glm::vec3{10, 20, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.9, 1});
    m_Registry.emplace<CircleColliderComponent>(circleEntity, 1.0f);

    //------------------------------------------------------------------//

    m_Registry.emplace<TransformComponent>(
        circleEntity2, TransformComponent{glm::vec3(20.f, 0.0f, 0.f), glm::vec3(0, 0, 0), glm::vec3(1.f)});

    m_Registry.emplace<PhysicsComponent>(
        circleEntity2, PhysicsComponent{glm::vec3{-9999999, 100, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.9, 100});
    m_Registry.emplace<CircleColliderComponent>(circleEntity2, 1.0f);
*/
    // creates buffers etc.

    entt::entity cube1 = m_Registry.create();

    m_Registry.emplace<MeshComponent>(cube1,

                                      generateCubeVertices(), generateCubeIndices());
    m_Registry.emplace<TransformComponent>(cube1, TransformComponent{
                                                      /*position*/ {0.0f, -5.0f, -20.0f}, // 5 units in front of camera
                                                      /*rotation*/ {0.0f, 30.0f, 30.0f},
                                                      /*scale*/ {10.0f, 1.0f, 10.0f} // big enough to fill the view
                                                  });
    m_Registry.emplace<PhysicsComponent>(
        cube1,

        PhysicsComponent{glm::vec3{0, 20, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.9, 1, true});

    m_Registry.emplace<OBBColliderComponent>(
        cube1, OBBColliderComponent{
                   glm::vec3(0.0f), {glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)}, glm::vec3(0.5f), glm::vec3(0.5f)});

    entt::entity cube2 = m_Registry.create();

    m_Registry.emplace<MeshComponent>(cube2,

                                      generateCubeVertices(), generateCubeIndices());
    m_Registry.emplace<TransformComponent>(cube2, TransformComponent{
                                                      /*position*/ {0.0f, 0.0f, -20.0f}, // 5 units in front of camera
                                                      /*rotation*/ {30.0f, 30.0f, 0.0f},
                                                      /*scale*/ {1.0f, 1.0f, 1.0f} // big enough to fill the view
                                                  });
    m_Registry.emplace<PhysicsComponent>(
        cube2,

        PhysicsComponent{glm::vec3{0, 0, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.3, 1, false});

    m_Registry.emplace<OBBColliderComponent>(
        cube2, OBBColliderComponent{
                   glm::vec3(0.0f), {glm::vec3(1, 0, 0),
                       glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)}, glm::vec3(0.5f),glm::vec3(0.5f)});

    RenderSystem::initializeMesh(m_Registry);
}

void Scene::main(double dt)
{
    // a) Update physics (integrate transforms)

    physicsSystem.update(static_cast<float>(dt));
    // b) Sync OBB colliders to match updated transforms
    collisionSystem.SyncOBBCollider();


    // c) Check collisions (fires events)
    // collisionSystem.CheckCollisions();    // Circle collisions
    collisionSystem.CheckOBBCollisions(); // OBB-vs-OBB SAT

    // collisionSystem.CheckWallCollisions(); // Optional wall checks

    // d) Dispatch all events to subscribed handlers
    m_Dispatcher.update();

    // e) Update other systems (e.g., camera)
    cameraSystem.update(m_Registry);

    // f) Render the frame
    renderSystem.render();
}

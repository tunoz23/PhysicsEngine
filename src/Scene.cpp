//
// Created by Tuna Öztürk on 29.03.2025.
//
#include "headers/Scene.h"

#include "CameraComponent.h"
#include "Circle.h"
#include "CircleColliderComponent.h"
#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Rectangle.h"
#include "TransformComponent.h"
#include "Cube.h"
#include "ActiveCameraData.h"

Scene::Scene(Shader p_Shader)
    : renderSystem(RenderSystem(p_Shader, m_Registry)), physicsSystem(PhysicsSystem(m_Registry, m_Dispatcher)),
      collisionSystem(CollisionSystem(m_Registry, m_Dispatcher))
{
    physicsSystem.subscribe(m_Dispatcher);


    // … inside Scene::Scene(Shader p_Shader) …

    // 1) Create the camera entity at the origin, looking toward –Z
    entt::entity cameraEntity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(
        cameraEntity,
        TransformComponent{
            /* position */ {0.0f, 0.0f,  -50.0f},
            /* rotation */ {0.0f, 0.0f,  0.0f},
            /* scale    */ {1.0f, 1.0f,  1.0f}
        }
    );
    m_Registry.emplace<CameraComponent>(
        cameraEntity,
        CameraComponent{
            .aspectRatio = 16.0f/9.0f,
            .near        = 0.1f,
            .far         = 100.0f,
            .fov         = 45.0f
        }
    );

    // Debug quad at Z = -5
    entt::entity debugQuad = m_Registry.create();
    m_Registry.emplace<MeshComponent>(
        debugQuad,

        generateCubeVertices(),
        generateCubeIndices()
    );
    m_Registry.emplace<TransformComponent>(
        debugQuad,
        TransformComponent{
            /*position*/ {0.0f, 0.0f, -5.0f},  // 5 units in front of camera
            /*rotation*/ {0.0f, 0.0f,  0.0f},
            /*scale*/    {3.0f, 3.0f, 3.0f}    // big enough to fill the view
        }
    );
    m_Registry.emplace<PhysicsComponent>(debugQuad,

        PhysicsComponent{glm::vec3{0, 20, 0}, glm::vec3{0, 0, 0}, glm::vec3{0}, 0.9, 1});


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

    RenderSystem::initializeMesh(m_Registry);
}

void Scene::main(double dt)
{
    // TO DO: these two have some problems.
//    collisionSystem.CheckCollisions();
//    collisionSystem.CheckWallCollisions();

   // m_Dispatcher.update();

    physicsSystem.update(static_cast<float>(dt));
    auto tview = m_Registry.view<MeshComponent, TransformComponent>();
    for(auto& entity : tview)
    {
        auto [meshcomp, Transformcomp] = m_Registry.get<MeshComponent,TransformComponent>(entity);

        Transformcomp.rotation += glm::vec3(90.f*dt,90.f*dt,0.f);
    }
    cameraSystem.update(m_Registry);
    renderSystem.render();
}

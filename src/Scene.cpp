//
// Created by Tuna Öztürk on 29.03.2025.
//
#include "headers/Scene.h"
#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "CircleColliderComponent.h"
#include "Circle.h"


Scene::Scene(Shader shader)
	:renderSystem(RenderSystem(shader, m_Registry)), physicsSystem(PhysicsSystem(m_Registry, m_Dispatcher)), collisionSystem(CollisionSystem(m_Registry, m_Dispatcher))
{

	physicsSystem.subscribe(m_Dispatcher);
    entt::entity circleEntity = m_Registry.create();
    entt::entity circleEntity2 = m_Registry.create();

    int N = 16;
    m_Registry.emplace<MeshComponent>(circleEntity, generateCircleVertices(N), generateCircleIndices(N));
    m_Registry.emplace<MeshComponent>(circleEntity2, generateCircleVertices(N), generateCircleIndices(N));



    m_Registry.emplace<TransformComponent>(circleEntity,TransformComponent
        {glm::vec3(-20.f,0.0f,0.f),
            glm::vec3(0,0,0),
            glm::vec3(1.f)});


    m_Registry.emplace<PhysicsComponent>(circleEntity,PhysicsComponent{
        glm::vec3{10,20,0},
        glm::vec3{0,0,0},
        glm::vec3{0},
        0
    });
	m_Registry.emplace<CircleColliderComponent>(circleEntity,1.0f);

    //------------------------------------------------------------------//

    m_Registry.emplace<TransformComponent>(circleEntity2, TransformComponent
        { glm::vec3(20.f,0.0f,0.f),
            glm::vec3(0,0,0),
            glm::vec3(1.f) });


    m_Registry.emplace<PhysicsComponent>(circleEntity2, PhysicsComponent{
        glm::vec3{-10,20,0},
        glm::vec3{0,0,0},
        glm::vec3{0},
        0
        });
    m_Registry.emplace<CircleColliderComponent>(circleEntity2, 1.0f);





    //creates buffers etc.
    RenderSystem::initializeMesh(m_Registry);
}

void Scene::main(double dt)
{
    collisionSystem.CheckCollisions();
    m_Dispatcher.update();

    physicsSystem.update(static_cast<float>(dt));
    renderSystem.render();


}

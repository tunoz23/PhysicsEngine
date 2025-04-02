//
// Created by Tuna Öztürk on 29.03.2025.
//
#include "headers/Scene.h"
#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "utils.h"
Scene::Scene(Shader shader)
    :renderSys(RenderSystem(shader))
{

    entt::entity e = m_Registry.create();



    m_Registry.emplace<MeshComponent>(e,std::vector<float> {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    },
    std::vector<unsigned int> {0, 1, 2});



    m_Registry.emplace<TransformComponent>(e,TransformComponent
        {glm::vec3(-10.f,0.0f,0.f),
            glm::vec3(0,0,90.f),
            glm::vec3(10.f)});


    m_Registry.emplace<PhysicsComponent>(e,PhysicsComponent{
        glm::vec3{0,30,0},
        glm::vec3{0,0,0},
        glm::vec3{0},
        10
    });



    entt::entity e1 = m_Registry.create();



    m_Registry.emplace<MeshComponent>(e1,std::vector<float> {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    },
    std::vector<unsigned int> {0, 1, 2});



    m_Registry.emplace<TransformComponent>(e1,TransformComponent
        {glm::vec3(0.f,0.0f,0.f),
            glm::vec3(0,0,0.f),
            glm::vec3(1.f)});


    m_Registry.emplace<PhysicsComponent>(e1,PhysicsComponent{
        glm::vec3{0,0,0},
        glm::vec3{0,0,0},
        glm::vec3{0},
        0
    });


    entt::entity circleEntity = m_Registry.create();

    int N = 128;
    m_Registry.emplace<MeshComponent>(circleEntity, generateCircleVertices(N), generateCircleIndices(N));




    m_Registry.emplace<TransformComponent>(circleEntity,TransformComponent
        {glm::vec3(-20.f,0.0f,0.f),
            glm::vec3(0,0,90.f),
            glm::vec3(1.f)});


    m_Registry.emplace<PhysicsComponent>(circleEntity,PhysicsComponent{
        glm::vec3{10,20,0},
        glm::vec3{0,0,0},
        glm::vec3{0},
        50
    });



    //creates buffers etc.
    RenderSystem::initializeMesh(m_Registry);
}

void Scene::main(float dt)
{

    PhysicsSystem::update(m_Registry,dt);
    renderSys.render(m_Registry);


}

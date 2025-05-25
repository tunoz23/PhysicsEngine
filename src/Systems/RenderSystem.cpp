//
// Created by Tuna Öztürk on 29.03.2025.
//

#include "RenderSystem.h"

#include "TransformComponent.h"
#include "ActiveCameraData.h"
RenderSystem::RenderSystem(Shader shader, entt::registry &registry) : m_Shader(shader), m_Registry(registry)
{
}

void RenderSystem::render(const MeshComponent &meshComponent) const
{
    m_Shader.use();

    glBindVertexArray(meshComponent.vao);
    glDrawElements(GL_TRIANGLES, meshComponent.indices.size(), GL_UNSIGNED_INT, nullptr);
}
void RenderSystem::render() const
{
    m_Shader.use();

    //Debug Purproses
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Load camera matrices from context
    if (m_Registry.ctx().contains<ActiveCameraData>())
    {
        const auto &cam = m_Registry.ctx().get<ActiveCameraData>();

        glm::mat4 view = glm::lookAt(glm::vec3(0,0,3.f), glm::vec3{0}, glm::vec3(0,1.f,0));        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.f), 16.f/9.f, 0.1f, 100.f);
        //glm::lookAt(const vec<3, T, Q> &eye, const vec<3, T, Q> &center, const vec<3, T, Q> &up)
        m_Shader.setMat4("view", cam.view);
        m_Shader.setMat4("projection", cam.projection);

    }
    else
    {
        std::cerr << "[RenderSystem] Warning: No CameraData found in context!" << std::endl;
    }

    // Optionally enable wireframe

    auto view = m_Registry.view<TransformComponent, MeshComponent>();
    for (const auto entity : view)
    {
        auto &transformComponent = view.get<TransformComponent>(entity);
        auto &meshComponent = view.get<MeshComponent>(entity);

        m_Shader.setMat4("model", transformComponent.getMatrix());

        glBindVertexArray(meshComponent.vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(meshComponent.indices.size()), GL_UNSIGNED_INT, nullptr);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "[initializeMesh] GL error 0x"
                      << std::hex << err << std::dec << std::endl;
        }
    }



}

void RenderSystem::initializeMesh(entt::registry &registry)
{
    auto view = registry.view<MeshComponent>();
    for (auto entity : view)
    {
        auto &mesh = view.get<MeshComponent>(entity);

        // Generate and bind VAO
        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        // Generate and bind VBO, then fill with vertex data
        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

        // Set up vertex attribute pointer for positions (3 floats per vertex)
        // Position Vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);


        glEnableVertexAttribArray(0);

        // Generate and bind EBO, then fill with index data
        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(),
                     GL_STATIC_DRAW);

        // Unbind the VAO (the EBO remains bound as part of VAO state)
        glBindVertexArray(0);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "[initializeMesh] GL error 0x"
                      << std::hex << err << std::dec << std::endl;
        }

    }
}

float RenderSystem::aspectRatio = 16.f / 9.0f;
float RenderSystem::windowLeft = -25.f;
float RenderSystem::windowRight = 25.f;
float RenderSystem::windowBottom = -25.f;
float RenderSystem::windowTop = 25.f;

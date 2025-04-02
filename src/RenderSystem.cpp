//
// Created by Tuna Öztürk on 29.03.2025.
//

#include "RenderSystem.h"

#include "Scene.h"
#include "TransformComponent.h"

RenderSystem::RenderSystem(Shader shader)
    :m_Shader(shader)
{

}

void RenderSystem::render(const MeshComponent& meshComponent) const {
    m_Shader.use();

    glBindVertexArray(meshComponent.vao);
    glDrawElements(GL_TRIANGLES, meshComponent.indices.size(), GL_UNSIGNED_INT, nullptr);


}

void RenderSystem::render(entt::registry &registry) const {
    m_Shader.use();

    //DEBUG PURPOSES
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::mat4 projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);
    m_Shader.setMat4("projection", projection);

    // Iterate over entities that have both TransformComponent and MeshComponent
    auto view = registry.view<TransformComponent, MeshComponent>();
    for (auto entity : view) {
        auto& transformComponent = view.get<TransformComponent>(entity);
        auto& meshComponent = view.get<MeshComponent>(entity);

        // Set the model matrix for this entity
        m_Shader.setMat4("model", transformComponent.getMatrix());

        // Bind the VAO and draw the mesh using its indices
        glBindVertexArray(meshComponent.vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(meshComponent.indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}





void RenderSystem::initializeMesh(entt::registry& registry) {
    auto view = registry.view<MeshComponent>();
    for (auto entity : view) {
        auto& mesh = view.get<MeshComponent>(entity);

        // Generate and bind VAO
        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        // Generate and bind VBO, then fill with vertex data
        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

        // Set up vertex attribute pointer for positions (3 floats per vertex)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Generate and bind EBO, then fill with index data
        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

        // Unbind the VAO (the EBO remains bound as part of VAO state)
        glBindVertexArray(0);
    }
}

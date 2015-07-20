#include <framework/renderer/instancerenderer.h>

Framework::Renderer::InstanceRenderer::InstanceRenderer(ProgramLinker &shaderProgram, GLuint modelDataBuffer)
    : shaderProgram(shaderProgram), modelDataBuffer(modelDataBuffer)
{
    glGenBuffers(1, &instanceDataBuffer);
    glGenVertexArrays(1, &instanceDataArray);

}

Framework::Renderer::InstanceRenderer::~InstanceRenderer()
{
    glDeleteVertexArrays(1, &instanceDataArray);
    glDeleteBuffers(1, &instanceDataBuffer);
}

void Framework::Renderer::InstanceRenderer::enableVertexAttribPointer(
    GLuint vertexAttributeIndex,
    GLint componentSize,
    GLenum dataType,
    GLboolean isDataNormalized,
    GLsizei dataStride,
    GLvoid *dataPointer
)
{
    glBindBuffer(GL_ARRAY_BUFFER, modelDataBuffer);
    glBindVertexArray(instanceDataArray);
    glEnableVertexAttribArray(vertexAttributeIndex);
    glVertexAttribPointer(
        vertexAttributeIndex,
        componentSize,
        dataType,
        isDataNormalized,
        dataStride,
        dataPointer
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Framework::Renderer::InstanceRenderer::render(const std::vector<Framework::Sprite::SpriteInstanceData> &instanceDataCollection)
{
    shaderProgram.use();
    glBindVertexArray(instanceDataArray);
    glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        instanceDataCollection.size() * sizeof(Framework::Sprite::SpriteInstanceData),
        instanceDataCollection.data(),
        GL_DYNAMIC_DRAW
    );
    //glDrawElements call here to use only 4 vertices, instead of 6 per quad
    // glBufferData(GL_ARRAY_BUFFER, spriteModelMatrices.size() * sizeof(glm::mat4), spriteModelMatrices.data(), GL_DYNAMIC_DRAW);
    // glDrawArraysInstanced(GL_TRIANGLES, 0, 6, spriteModelMatrices.size());
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // shaderProgram.unuse(); <-- need to fix, currently unuse frees the sprite from GPU. should remove that behavior
}

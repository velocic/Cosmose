#include <framework/renderer/instancerenderer.h>

Framework::Renderer::InstanceRenderer::InstanceRenderer(ProgramLinker &shaderProgram, GLuint modelDataBuffer)
    : shaderProgram(shaderProgram), modelDataBuffer(modelDataBuffer)
{
    glGenBuffers(1, &instanceDataBuffer);
    glGenVertexArrays(1, &instanceDataArray);

    //Set up VAO for the hard-coded model vertices
    glBindBuffer(GL_ARRAY_BUFFER, modelDataBuffer);
    glBindVertexArray(instanceDataArray);
    //consider searching for a glsl attribute here, rather than
    //using index 0 by default
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
    glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer);
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
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instanceDataCollection.size());
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // shaderProgram.unuse(); <-- need to fix, currently unuse frees the sprite from GPU. should remove that behavior
}

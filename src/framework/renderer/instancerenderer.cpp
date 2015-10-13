#include <framework/renderer/instancerenderer.h>

Framework::Renderer::InstanceRenderer::InstanceRenderer(ProgramLinker &shaderProgram, GLuint modelDataBuffer, GLuint indexDataBuffer)
    : shaderProgram(shaderProgram), modelDataBuffer(modelDataBuffer), indexDataBuffer(indexDataBuffer)
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
    GLvoid *dataPointer,
    GLuint vertexAttributeDivisor
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
    glVertexAttribDivisor(vertexAttributeIndex, vertexAttributeDivisor);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Framework::Renderer::InstanceRenderer::render(
    const Framework::Sprite::SpriteInstanceData *instanceDataCollection,
    std::weak_ptr<OpenGL::Texture> spriteTexture,
    unsigned int instanceDataCollectionSize,
    unsigned int instanceDataCollectionSizeInBytes
)
{
    if (spriteTexture.expired()) {
        throw std::logic_error("Error: tried to bind a null texture at render time.");
    }

    shaderProgram.use();
    spriteTexture.lock()->bind();
    glBindVertexArray(instanceDataArray);
    glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        instanceDataCollectionSizeInBytes,
        instanceDataCollection,
        GL_DYNAMIC_DRAW
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexDataBuffer);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void *)0, instanceDataCollectionSize);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // shaderProgram.unuse(); <-- need to fix, currently unuse frees the sprite from GPU. should remove that behavior
}

#include <framework/renderer/instancerenderer.h>

Framework::Renderer::InstanceRenderer::InstanceRenderer(ProgramLinker shaderProgram, GLuint modelDataBuffer)
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

void Framework::Renderer::InstanceRenderer::render(std::vector<Framework::Sprite::BasicSprite> &spriteCollection)
{
    //TODO: clean this giant mess. just trying to get a basic working example right now
    std::vector<glm::mat4> spriteModelMatrices;
    for (auto it = spriteCollection.begin(); it != spriteCollection.end(); ++it) {
        spriteModelMatrices.push_back(it->getModelMatrix());
    }
    //use program
    shaderProgram.use();
    spriteCollection[0].getTexture()->bind();
    //bind buffers
    glBindBuffer(GL_ARRAY_BUFFER, modelDataBuffer);
    glBindVertexArray(instanceDataArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    //fill instanceDataBuffer with instance data, then set up attrib pointers
    glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer);
    glBufferData(GL_ARRAY_BUFFER, spriteModelMatrices.size() * sizeof(glm::mat4), spriteModelMatrices.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid *)0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid *)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid *)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid *)(3 * sizeof(glm::vec4)));
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    // glBindVertexArray(0);
    //do rendering (1 draw call per unique texture) (use glDrawElements to send 4 vertices instead of 6)
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, spriteModelMatrices.size());


    //unbind buffers
    shaderProgram.unuse();
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Framework::Renderer::InstanceRenderer::sortSpriteCollectionByTexture(
    std::vector<Framework::Sprite::BasicSprite> &spriteCollection
)
{
    std::sort(
        spriteCollection.begin(),
        spriteCollection.end(),
        [](const Framework::Sprite::BasicSprite &sprite1, const Framework::Sprite::BasicSprite &sprite2) {
            return sprite1.getTexture()->getName() < sprite2.getTexture()->getName();
        }
    );
}

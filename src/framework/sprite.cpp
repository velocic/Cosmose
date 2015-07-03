#include <framework/sprite.h>

glm::mat4 Framework::Sprite::getModelMatrix()
{
    return modelMatrix;
}

std::shared_ptr<OpenGL::Texture> Framework::Sprite::getTexture()
{
    return spriteTexture;
}

void Framework::Sprite::rotate(float rotationAngle, glm::vec3 rotationAxis)
{
    modelMatrix = glm::rotate(modelMatrix, rotationAngle, rotationAxis);
}

void Framework::Sprite::scale(glm::vec3 scaleVector)
{
    modelMatrix = glm::scale(modelMatrix, scaleVector);
}

void Framework::Sprite::translate(glm::vec3 translationVector)
{
    modelMatrix = glm::translate(modelMatrix, translationVector);
}

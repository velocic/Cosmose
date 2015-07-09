#include <framework/sprite/basicsprite.h>

glm::mat4 Framework::Sprite::BasicSprite::getModelMatrix()
{
    return modelMatrix;
}

std::shared_ptr<OpenGL::Texture> Framework::Sprite::BasicSprite::getTexture() const
{
    return spriteTexture;
}

void Framework::Sprite::BasicSprite::rotate(float rotationAngle, glm::vec3 rotationAxis)
{
    modelMatrix = glm::rotate(modelMatrix, rotationAngle, rotationAxis);
}

void Framework::Sprite::BasicSprite::scale(glm::vec3 scaleVector)
{
    modelMatrix = glm::scale(modelMatrix, scaleVector);
}

void Framework::Sprite::BasicSprite::translate(glm::vec3 translationVector)
{
    modelMatrix = glm::translate(modelMatrix, translationVector);
}

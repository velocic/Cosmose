#include <framework/sprite/basicsprite.h>

const Framework::Sprite::SpriteInstanceData &Framework::Sprite::BasicSprite::getInstanceData() const
{
    return instanceData;
}

unsigned int Framework::Sprite::BasicSprite::getInstanceID() const
{
    return instanceID;
}

std::shared_ptr<OpenGL::Texture> Framework::Sprite::BasicSprite::getTexture() const
{
    return spriteTexture;
}

void Framework::Sprite::BasicSprite::rotate(float rotationAngle, glm::vec3 rotationAxis)
{
    instanceData.MVPMatrix = glm::rotate(instanceData.MVPMatrix, rotationAngle, rotationAxis);
}

void Framework::Sprite::BasicSprite::scale(glm::vec3 scaleVector)
{
    instanceData.MVPMatrix = glm::scale(instanceData.MVPMatrix, scaleVector);
}

void Framework::Sprite::BasicSprite::translate(glm::vec3 translationVector)
{
    instanceData.MVPMatrix = glm::translate(instanceData.MVPMatrix, translationVector);
}

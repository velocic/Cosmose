#include <framework/sprite/basicsprite.h>

Framework::Sprite::BasicSprite::BasicSprite(
    std::weak_ptr<OpenGL::Texture> spriteTexture,
    SpriteInstanceData &instanceData,
    SpriteInstanceDataArray &parentInstanceCollection
) :
    spriteTexture(spriteTexture),
    parentInstanceCollection(parentInstanceCollection),
    instanceData(instanceData)
{
    //hard-code BasicSprite's texture coordinates to
    //just use the full texture size
    instanceData.textureCoordinates.textureCoordinate1 = glm::vec2(0.0f, 0.0f);
    instanceData.textureCoordinates.textureCoordinate2 = glm::vec2(1.0f, 0.0f);
    instanceData.textureCoordinates.textureCoordinate3 = glm::vec2(1.0f, 1.0f);
    instanceData.textureCoordinates.textureCoordinate4 = glm::vec2(0.0f, 1.0f);
}

Framework::Sprite::BasicSprite::~BasicSprite()
{
    parentInstanceCollection.remove(instanceData.parentArrayIndex);
}

const Framework::Sprite::SpriteInstanceData &Framework::Sprite::BasicSprite::getInstanceData() const
{
    return instanceData;
}

std::weak_ptr<OpenGL::Texture> Framework::Sprite::BasicSprite::getTexture() const
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

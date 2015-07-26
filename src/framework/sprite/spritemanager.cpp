#include <framework/sprite/spritemanager.h>

Framework::Sprite::SpriteManager::SpriteManager(
    OpenGL::TextureCache &textureCache,
    std::string texturePath,
    unsigned int spriteCollectionMaxSize
) :
    textureCache(textureCache),
    texturePath(texturePath),
    instanceDataCollection(SpriteInstanceDataArray(spriteCollectionMaxSize))
{}

const Framework::Sprite::SpriteInstanceData *Framework::Sprite::SpriteManager::getInstanceData() const
{
    return instanceDataCollection.getCollection();
}

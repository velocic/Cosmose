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

unsigned int Framework::Sprite::SpriteManager::getInstanceDataCollectionSize() const
{
    return instanceDataCollection.getSize();
}

unsigned int Framework::Sprite::SpriteManager::getInstanceDataCollectionSizeInBytes() const
{
    return instanceDataCollection.getSizeInBytes();
}

std::unique_ptr<Framework::Sprite::BasicSprite> Framework::Sprite::SpriteManager::getBasicSprite()
{
    std::unique_ptr<Framework::Sprite::BasicSprite> spritePointer(
        new Framework::Sprite::BasicSprite(
            textureCache.getTexture(texturePath),
            instanceDataCollection.insert(),
            instanceDataCollection
        )
    );
    return spritePointer;
}

std::unique_ptr<Framework::Sprite::BasicSprite> Framework::Sprite::SpriteManager::getBasicSprite(Framework::Sprite::BasicSprite sourceSprite)
{
    std::unique_ptr<Framework::Sprite::BasicSprite> spritePointer(
        new Framework::Sprite::BasicSprite(
            textureCache.getTexture(texturePath),
            instanceDataCollection.insert(sourceSprite.getInstanceData()),
            instanceDataCollection
        )
    );
    return spritePointer;
}

std::unique_ptr<Framework::Sprite::ScrollingSprite> Framework::Sprite::SpriteManager::getScrollingSprite(
    float UVCoordinateAdvancementAmount,
    unsigned int frameDelay,
    float scrollingViewportTextureWidth
)
{
    std::unique_ptr<Framework::Sprite::ScrollingSprite> spritePointer(
        new Framework::Sprite::ScrollingSprite(
            textureCache.getTexture(texturePath),
            instanceDataCollection.insert(),
            instanceDataCollection,
            UVCoordinateAdvancementAmount,
            frameDelay,
            scrollingViewportTextureWidth
        )
    );
    return spritePointer;
}

std::unique_ptr<Framework::Sprite::ScrollingSprite> Framework::Sprite::SpriteManager::getScrollingSprite(
    float UVCoordinateAdvancementAmount,
    unsigned int frameDelay,
    float scrollingViewportTextureWidth,
    Framework::Sprite::ScrollingSprite sourceSprite
)
{
    std::unique_ptr<Framework::Sprite::ScrollingSprite> spritePointer(
        new Framework::Sprite::ScrollingSprite(
            textureCache.getTexture(texturePath),
            instanceDataCollection.insert(sourceSprite.getInstanceData()),
            instanceDataCollection,
            UVCoordinateAdvancementAmount,
            frameDelay,
            scrollingViewportTextureWidth
        )
    );
    return spritePointer;
}

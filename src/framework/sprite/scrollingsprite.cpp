#include <framework/sprite/scrollingsprite.h>

Framework::Sprite::ScrollingSprite::ScrollingSprite(
    std::weak_ptr<OpenGL::Texture> spriteTexture,
    SpriteInstanceData &instanceData,
    SpriteInstanceDataArray &parentInstanceCollection,
    float UVCoordinateAdvancementAmount,
    unsigned int frameDelay,
    float scrollingViewportTextureWidth
) :
    BasicSprite(spriteTexture, instanceData, parentInstanceCollection),
    UVCoordinateAdvancementAmount(UVCoordinateAdvancementAmount),
    frameDelay(frameDelay),
    framesDrawn(0)
{
    if (scrollingViewportTextureWidth > 1.0f) {
        throw std::logic_error("Error: Tried to set scrolling texture viewport larger than 100% of texture width");
    }
    instanceData.textureCoordinates.textureCoordinate1 = glm::vec2(0.0f, 0.0f);
    instanceData.textureCoordinates.textureCoordinate2 = glm::vec2(1.0f, 0.0f);
    instanceData.textureCoordinates.textureCoordinate3 = glm::vec2(1.0f, scrollingViewportTextureWidth);
    instanceData.textureCoordinates.textureCoordinate4 = glm::vec2(0.0f, 0.0f);
    instanceData.textureCoordinates.textureCoordinate5 = glm::vec2(0.0f, scrollingViewportTextureWidth);
    instanceData.textureCoordinates.textureCoordinate6 = glm::vec2(1.0f, scrollingViewportTextureWidth);
}

void Framework::Sprite::ScrollingSprite::advanceFrameCount()
{
    ++framesDrawn;

    if ((framesDrawn % frameDelay) == 0) {
        scrollUVCoordinates();
    }
}

void Framework::Sprite::ScrollingSprite::scrollUVCoordinates()
{
    instanceData.textureCoordinates.textureCoordinate1.x += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate2.x += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate3.x += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate4.x += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate5.x += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate6.x += UVCoordinateAdvancementAmount;
}

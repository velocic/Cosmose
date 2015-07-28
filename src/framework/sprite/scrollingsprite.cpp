#include <framework/sprite/scrollingsprite.h>

Framework::Sprite::ScrollingSprite::ScrollingSprite(
    std::shared_ptr<OpenGL::Texture> spriteTexture,
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
        throw std::logic_error("Error: Tried to set scrolling viewport texture with larger than 100% of texture width");
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

    if (frameDelay % framesDrawn == 0) {
        scrollUVCoordinates();
    }
}

void Framework::Sprite::ScrollingSprite::scrollUVCoordinates()
{
    instanceData.textureCoordinates.textureCoordinate1 += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate2 += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate3 += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate4 += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate5 += UVCoordinateAdvancementAmount;
    instanceData.textureCoordinates.textureCoordinate6 += UVCoordinateAdvancementAmount;
}

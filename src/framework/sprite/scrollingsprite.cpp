#include <framework/sprite/scrollingsprite.h>

Framework::Sprite::ScrollingSprite::ScrollingSprite(
    std::shared_ptr<OpenGL::Texture> spriteTexture,
    SpriteInstanceData &instanceData,
    SpriteInstanceDataArray &parentInstanceCollection,
    float UVCoordinateAdvancementAmount,
    unsigned int frameDelay
) :
    BasicSprite(spriteTexture, instanceData, parentInstanceCollection),
    UVCoordinateAdvancementAmount(UVCoordinateAdvancementAmount),
    frameDelay(frameDelay),
    framesDrawn(0)
{}

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

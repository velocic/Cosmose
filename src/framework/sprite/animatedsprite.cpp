#include <framework/sprite/animatedsprite.h>

Framework::Sprite::AnimatedSprite::AnimatedSprite(
    std::weak_ptr<OpenGL::Texture> spriteTexture,
    SpriteInstanceData &instanceData,
    SpriteInstanceDataArray &parentInstanceCollection,
    std::weak_ptr<AnimationGroup> animations,
    std::string startingAnimation,
    unsigned int framesBetweenAnimationCells
) :
    BasicSprite(spriteTexture, instanceData, parentInstanceCollection),
    animations(animations),
    framesBetweenAnimationCells(framesBetweenAnimationCells)
    currentAnimation(startingAnimation),
    framesDrawn(0)
    currentAnimationFrameIndex(0)
{
}

void Framework::Sprite::AnimatedSprite::advanceAnimation()
{
    std::shared_ptr<AnimationGroup> animationGroup = animations.lock();

    if (currentAnimationFrameIndex >= animationGroup->getAnimationData(currentAnimation).animationCellCount) {
        currentAnimationFrameIndex = 0;
    }

    instanceData.textureCoordinates = animationGroup->getAnimationFrame(currentAnimation, currentAnimationFrameIndex);
}

void Framework::Sprite::AnimatedSprite::advanceFrameCount()
{
    ++framesDrawn;

    if (framesDrawn == framesBetweenAnimationCells) {
        framesDrawn = 0;

        advanceAnimation();
    }
}

void Framework::Sprite::AnimatedSprite::changeAnimation(std::string newAnimation)
{
    currentAnimation = newAnimation;
    currentAnimationFrameIndex = 0;
    framesDrawn = 0;
}

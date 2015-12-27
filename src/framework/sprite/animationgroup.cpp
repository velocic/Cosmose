#include <framework/sprite/animationgroup.h>

Framework::Sprite::AnimationGroup::AnimationGroup()
{
}

const SpriteTextureCoordinates &Framework::Sprite::AnimationGroup::getAnimationFrame(std::string animationName, unsigned int sequenceNumber)
{
    return animations[animationName][sequenceNumber];
}

const AnimationMetaData &Framework::Sprite::AnimationGroup::getAnimationData(std::string animationName)
{
    return animationData[animationName];
}

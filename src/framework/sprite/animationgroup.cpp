#include <framework/sprite/animationgroup.h>

const Framework::Sprite::SpriteTextureCoordinates &Framework::Sprite::AnimationGroup::getAnimationFrame(std::string animationName, unsigned int sequenceNumber)
{
    return animations[animationName][sequenceNumber];
}

const Framework::Sprite::AnimationMetaData &Framework::Sprite::AnimationGroup::getAnimationData(std::string animationName)
{
    return animationData[animationName];
}

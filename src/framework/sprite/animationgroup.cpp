#include <framework/sprite/animationgroup.h>

Framework::Sprite::AnimationGroup::AnimationGroup()
{
    //TODO: fill in once format of spritesheet coordinate file looks like
}

const SpriteTextureCoordinates &Framework::Sprite::AnimationGroup::getAnimationFrame(std::string animationName, unsigned int sequenceNumber)
{
    return animations[animationName][sequenceNumber];
}

const AnimationMetaData &Framework::Sprite::AnimationGroup::getAnimationData(std::string animationName)
{
    return animationData[animationName];
}

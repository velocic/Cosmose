#ifndef ANIMATIONGROUP_H
#define ANIMATIONGROUP_H

#include <framework/sprite/animationmetadata.h>
#include <string>
#include <unordered_map>

namespace Framework
{
    namespace Sprite
    {
        class AnimationGroup
        {
            private:
                std::unordered_map<std::string, std::vector<SpriteTextureCoordinates>> animations;
                std::unordered_map<std::string, AnimationMetaData> animationData;
            public:
                //copy constructor
                AnimationGroup(
                    std::unordered_map<std::string, std::vector<SpriteTextureCoordinates>> &animations,
                    std::unordered_map<std::string, AnimationMetaData> &animationData
                ) : 
                    animations(animations),
                    animationData(animationData)
                {}

                //move constructor
                AnimationGroup(
                    std::unordered_map<std::string, std::vector<SpriteTextureCoordinates>> &&animations,
                    std::unordered_map<std::string, AnimationMetaData> &&animationData
                ) :
                    animations(std::move(animations)),
                    animationData(std::move(animationData))
                {}

                const SpriteTextureCoordinates &getAnimationFrame(std::string animationName, unsigned int sequenceNumber);
                const AnimationMetaData &getAnimationData(std::string animationName);
        };
    }
}

#endif

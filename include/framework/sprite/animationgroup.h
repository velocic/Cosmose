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
                AnimationGroup();
                const SpriteTextureCoordinates &getAnimationFrame(std::string animationName, unsigned int sequenceNumber);
                const AnimationMetaData &getAnimationData(std::string animationName);
        };
    }
}

#endif

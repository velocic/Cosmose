#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <framework/sprite/spritetexturecoordinates.h>
#include <opengl/texture.h>
#include <memory>
#include <vector>

namespace Framework
{
    namespace Sprite
    {
        class AnimatedSprite : public BasicSprite
        {
            private:
                std::weak_ptr<AnimationGroup> animations;
                unsigned int framesBetweenAnimationCells;
                std::string currentAnimation;
                unsigned int framesDrawn;
                unsigned int currentAnimationFrameIndex;
                void advanceAnimation();
            public:
                AnimatedSprite(
                    std::weak_ptr<OpenGL::Texture> spriteTexture,
                    SpriteInstanceData &instanceData,
                    SpriteInstanceDataArray &parentInstanceCollection,
                    std::weak_ptr<AnimationGroup> animations,
                    std::string startingAnimation,
                    unsigned int framesBetweenAnimationCells
                );
                void advanceFrameCount();
                void changeAnimation(std::string newAnimation);
        };
    }
}

#endif

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <framework/sprite/animatedsprite.h>
#include <framework/sprite/basicsprite.h>
#include <framework/sprite/scrollingsprite.h>
#include <framework/sprite/spriteinstancedata.h>
#include <framework/sprite/spriteinstancedataarray.h>
#include <opengl/texture.h>
#include <memory>
#include <string>

namespace Framework
{
    namespace Sprite
    {
        class SpriteManager
        {

            private:
                std::shared_ptr<OpenGL::Texture> spriteTexture;
                SpriteInstanceDataArray instanceDataCollection;
            public:
                //Note: texture at texturePath needs to be loaded from textureCache
                //before we can use it here. That way of working should be redesigned.
                SpriteManager(
                    std::shared_ptr<OpenGL::Texture> spriteTexture,
                    unsigned int spriteCollectionMaxSize
                );
                ~SpriteManager();
                const SpriteInstanceData *getInstanceData() const;
                unsigned int getInstanceDataCollectionSize() const;
                unsigned int getInstanceDataCollectionSizeInBytes() const;
                std::unique_ptr<AnimatedSprite> getAnimatedSprite(
                    std::weak_ptr<AnimationGroup> animations,
                    std::string startingAnimation,
                    unsigned int framesBetweenAnimationCells
                );
                std::unique_ptr<BasicSprite> getBasicSprite();
                std::unique_ptr<BasicSprite> getBasicSprite(BasicSprite sourceSprite);
                std::unique_ptr<ScrollingSprite> getScrollingSprite(
                    float UVCoordinateAdvancementAmount,
                    unsigned int frameDelay,
                    float scrollingViewportTextureWidth
                );
                std::unique_ptr<ScrollingSprite> getScrollingSprite(
                    float UVCoordinateAdvancementAmount,
                    unsigned int frameDelay,
                    float scrollingViewportTextureWidth,
                    ScrollingSprite sourceSprite
                );
                std::weak_ptr<OpenGL::Texture> getSpriteTexture();
                void purge();
        };
    }
}

#endif

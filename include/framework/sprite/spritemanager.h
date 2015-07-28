#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <framework/sprite/spriteinstancedata.h>
#include <framework/sprite/spriteinstancedataarray.h>
#include <framework/sprite/basicsprite.h>
#include <framework/sprite/scrollingsprite.h>
#include <opengl/texturecache.h>
#include <memory>
#include <string>

namespace Framework
{
    namespace Sprite
    {
        class SpriteManager
        {
            private:
                OpenGL::TextureCache &textureCache;
                std::string texturePath;
                SpriteInstanceDataArray instanceDataCollection;
            public:
                //Note: texture at texturePath needs to be loaded from textureCache
                //before we can use it here. That way of working should be redesigned.
                SpriteManager(
                    OpenGL::TextureCache &textureCache,
                    std::string texturePath,
                    unsigned int spriteCollectionMaxSize
                );
                const SpriteInstanceData *getInstanceData() const;
                unsigned int getInstanceDataCollectionSize() const;
                unsigned int getInstanceDataCollectionSizeInBytes() const;
                std::unique_ptr<BasicSprite> getBasicSprite();
                std::unique_ptr<BasicSprite> getBasicSprite(BasicSprite sourceSprite);
                std::unique_ptr<ScrollingSprite> getScrollingSprite(
                    float UVCoordinateAdvancementAmount,
                    unsigned int frameDelay
                );
                std::unique_ptr<ScrollingSprite> getScrollingSprite(
                    float UVCoordinateAdvancementAmount,
                    unsigned int frameDelay,
                    ScrollingSprite sourceSprite
                );
        };
    }
}

#endif

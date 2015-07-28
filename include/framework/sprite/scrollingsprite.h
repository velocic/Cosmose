#ifndef SCROLLINGSPRITE_H
#define SCROLLINGSPRITE_H

#include <framework/sprite/basicsprite.h>
#include <memory>

namespace Framework
{
    namespace Sprite
    {
        class ScrollingSprite : public BasicSprite
        {
            private:
                float UVCoordinateAdvancementAmount;
                unsigned int frameDelay;
                unsigned int framesDrawn;
                void scrollUVCoordinates();
            public:
                ScrollingSprite(
                    std::shared_ptr<OpenGL::Texture> spriteTexture,
                    SpriteInstanceData &instanceData,
                    SpriteInstanceDataArray &parentInstanceCollection,
                    float UVCoordinateAdvancementAmount,
                    unsigned int frameDelay
                );
                void advanceFrameCount();
        };
    }
}

#endif

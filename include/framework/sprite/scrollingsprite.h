#ifndef SCROLLINGSPRITE_H
#define SCROLLINGSPRITE_H

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
                    float UVCoordinateAdvanceAmount,
                    unsigned int frameDelay
                );
                void advanceFrameCount();
        }
    }
}

#endif

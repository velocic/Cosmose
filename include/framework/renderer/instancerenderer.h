#ifndef INSTANCERENDERER_H
#define INSTANCERENDERER_H

#include <framework/sprite/basicsprite.h>
#include <opengl/programlinker.h>
#include <algorithm>
#include <vector>

namespace Framework
{
    namespace Renderer
    {
        class InstanceRenderer
        {
            private:
                ProgramLinker shaderProgram;
            public:
                Instance(ProgramLinker shaderProgram)
                    : shaderProgram(shaderProgram) {}
                void render(std::vector<Framework::Sprite::BasicSprite> &spriteCollection);
                void sortSpriteCollectionByTexture(std::vector<Framework::Sprite::BasicSprite> &spriteCollection);
        }
    }
}

#endif

#ifndef INSTANCERENDERER_H
#define INSTANCERENDERER_H

#include <framework/sprite/basicsprite.h>
#include <glm/glm.hpp>
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
                GLuint modelDataBuffer;
                GLuint instanceDataBuffer;
                GLuint instanceDataArray;
            public:
                InstanceRenderer(ProgramLinker shaderProgram, GLuint modelDataBuffer);
                ~InstanceRenderer();
                void render(std::vector<Framework::Sprite::BasicSprite> &spriteCollection);
                void sortSpriteCollectionByTexture(std::vector<Framework::Sprite::BasicSprite> &spriteCollection);
        };
    }
}

#endif

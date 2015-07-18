#ifndef SPRITEINSTANCEDATA_H
#define SPRITEINSTANCEDATA_H

#include <glm/glm.hpp>
#include <framework/sprite/spritetexturecoordinates.h>

namespace Framework
{
    namespace Sprite
    {
        struct SpriteInstanceData
        {
            glm::mat4 MVPMatrix;
            SpriteTextureCoordinates textureCoordinates;
            glm::vec4 colorModifier;
            bool isActive = true;
        };
    }
}

#endif

#ifndef ANIMATIONMETADATA_H
#define ANIMATIONMETADATA_H

#include <string>

namespace Framework
{
    namespace Sprite
    {
        struct AnimationMetaData
        {
            unsigned int framesBetweenAnimationCells = 0;
            unsigned int animationCellCount = 0;
        };
    }
}

#endif

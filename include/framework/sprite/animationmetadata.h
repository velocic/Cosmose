#ifndef ANIMATIONMETADATA_H
#define ANIMATIONMETADATA_H

#include <string>

namespace Framework
{
    namespace Sprite
    {
        struct AnimationMetaData
        {
            int defaultFramesBetweenAnimationCells;
            int animationCellCount;
            std::string animationName;
        };
    }
}

#endif

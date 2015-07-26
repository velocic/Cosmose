#ifndef SPRITEINSTANCEDATAARRAY_H
#define SPRITEINSTANCEDATAARRAY_H

#include <framework/sprite/spriteinstancedata.h>
#include <memory>
#include <stdexcept>

namespace Framework
{
    namespace Sprite 
    {
        class SpriteInstanceDataArray
        {
            private:
                const unsigned int maxSize;
                std::unique_ptr<SpriteInstanceData[]> collection;
                unsigned int currentSize;
            public:
                SpriteInstanceDataArray(unsigned int maxSize);
                ~SpriteInstanceDataArray();
                const SpriteInstanceData *getCollection() const;
                unsigned int getSize();
                unsigned int getSizeInBytes();
                SpriteInstanceData &insert(SpriteInstanceData element);
                void remove(unsigned int indexToRemove);
        };
    }
}
#endif

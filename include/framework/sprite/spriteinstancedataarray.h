#ifndef SPRITEINSTANCEDATAARRAY_H
#define SPRITEINSTANCEDATAARRAY_H

#include <framework/sprite/spriteinstancedata.h>
#include <memory>
#include <stdexcept>
#include <utility>

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
                //Explicitly mark this class as non-copyable since it holds a unique_ptr
                SpriteInstanceDataArray(SpriteInstanceDataArray const &) = delete;
                SpriteInstanceDataArray &operator=(SpriteInstanceDataArray const &) = delete;
                //Declare move constructor, move assignment so this object can be instantiated
                //in a managing object properly.
                SpriteInstanceDataArray(SpriteInstanceDataArray &&sourceObject);
                SpriteInstanceDataArray &operator=(SpriteInstanceDataArray &&sourceObject);
                SpriteInstanceDataArray(unsigned int maxSize);
                ~SpriteInstanceDataArray();
                const SpriteInstanceData *getCollection() const;
                unsigned int getSize() const;
                unsigned int getSizeInBytes() const;
                SpriteInstanceData &insert(SpriteInstanceData element);
                SpriteInstanceData &insert();
                void remove(unsigned int indexToRemove);
        };
    }
}
#endif

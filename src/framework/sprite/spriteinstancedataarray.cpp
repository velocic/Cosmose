#include <framework/sprite/spriteinstancedataarray.h>

Framework::Sprite::SpriteInstanceDataArray::SpriteInstanceDataArray(
    unsigned int maxSize
) :
    maxSize(maxSize),
    collection(new Framework::Sprite::SpriteInstanceData[maxSize]),
    currentSize(0)
{}

Framework::Sprite::SpriteInstanceDataArray::~SpriteInstanceDataArray()
{
    collection = nullptr;
}

const Framework::Sprite::SpriteInstanceData *Framework::Sprite::SpriteInstanceDataArray::getCollection() const
{
    return collection.get();
}

unsigned int Framework::Sprite::SpriteInstanceDataArray::getSize()
{
    return currentSize;
}

unsigned int Framework::Sprite::SpriteInstanceDataArray::getSizeInBytes()
{
    return (sizeof(Framework::Sprite::SpriteInstanceData) * currentSize);
}

Framework::Sprite::SpriteInstanceData &Framework::Sprite::SpriteInstanceDataArray::insert(Framework::Sprite::SpriteInstanceData element)
{
    if (currentSize >= maxSize) {
        throw std::logic_error("Error: Tried to insert an element into a full Framework::Sprite::SpriteInstanceDataArray.");
    }

    collection.get()[currentSize] = element;
    collection.get()[currentSize].parentArrayIndex = currentSize;
    ++currentSize;
    return collection.get()[currentSize-1];
}

void Framework::Sprite::SpriteInstanceDataArray::remove(unsigned int indexToRemove)
{
    collection.get()[indexToRemove] = collection.get()[currentSize-1];
    --currentSize;
}

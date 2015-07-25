#include <framework/sprite/spriteinstancedataarray.h>

Framework::Sprite::SpriteInstanceDataArray::SpriteInstanceDataArray(unsigned int maxSize)
    : maxSize(maxSize)
{
    collection = std::unique_ptr<SpriteInstanceData[]>(new SpriteInstanceData[maxSize]);
    currentSize = 0;
}

Framework::Sprite::SpriteInstanceDataArray::~SpriteInstanceDataArray()
{
    collection = nullptr;
}

const std::unique_ptr<SpriteInstanceData[]> Framework::Sprite::SpriteInstanceDataArray::getCollection() const
{
    return collection;
}

unsigned int Framework::Sprite::SpriteInstanceDataArray::getSize()
{
    return currentSize;
}

unsigned int Framework::Sprite::SpriteInstanceDataArray::getSizeInBytes()
{
    return (sizeof(SpriteInstanceData) * currentSize);
}

SpriteInstanceData &Framework::Sprite::SpriteInstanceDataArray::insert(SpriteInstanceData element)
{
    if (currentSize >= maxSize) {
        throw std::logic_error("Error: Tried to insert an element into a full Framework::Sprite::SpriteInstanceDataArray.");
    }

    collection[currentSize] = element;
    collection[currentSize].parentArrayIndex = currentSize;
    ++currentSize;
    return &collection[currentSize-1];
}

void Framework::Sprite::SpriteInstanceDataArray::remove(unsigned int indexToRemove)
{
    collection[indexToRemove] = collection[currentSize-1];
    --currentSize;
}

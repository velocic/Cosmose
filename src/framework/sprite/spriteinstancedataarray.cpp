#include <framework/sprite/spriteinstancedataarray.h>

//Move constructor
Framework::Sprite::SpriteInstanceDataArray::SpriteInstanceDataArray(
    Framework::Sprite::SpriteInstanceDataArray &&sourceObject
) :
    maxSize(sourceObject.maxSize),
    collection(std::move(sourceObject.collection))
{}

//Move operator
Framework::Sprite::SpriteInstanceDataArray &Framework::Sprite::SpriteInstanceDataArray::operator=(Framework::Sprite::SpriteInstanceDataArray &&sourceObject)
{
    //Check against moving collection from self to self
    if (this != &sourceObject) {
        collection = std::move(sourceObject.collection);
    }

    return *this;
}

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

unsigned int Framework::Sprite::SpriteInstanceDataArray::getSize() const
{
    return currentSize;
}

unsigned int Framework::Sprite::SpriteInstanceDataArray::getSizeInBytes() const
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

Framework::Sprite::SpriteInstanceData &Framework::Sprite::SpriteInstanceDataArray::insert()
{
    if (currentSize >= maxSize) {
        throw std::logic_error("Error: Tried to insert an element into a full Framework::Sprite::SpriteInstanceDataArray.");
    }

    Framework::Sprite::SpriteInstanceData element;
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

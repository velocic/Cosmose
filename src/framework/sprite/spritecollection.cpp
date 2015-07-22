#include <framework/sprite/spritecollection.h>

void Framework::Sprite::SpriteCollection::deleteInactiveSprites()
{
    //Note: this removal method has some serious overhead with larger collections.
    //It may not matter much in 2D (50k sprites @ 1.25% screen size w/ 640x480 resolution
    //dropped from 60fps to 41.5 fps). However, definitely consider switching to a faster
    //removal scheme
    //
    //At 100k sprites, this only reaches 45.4 fps even with this function disabled, so there
    //may be other bottlenecks compared to the prototyped implementation of instanced rendering
    instanceDataCollection.erase(
        std::remove_if(
            instanceDataCollection.begin(),
            instanceDataCollection.end(),
            [](SpriteInstanceData &currentInstanceData) -> bool {
                return currentInstanceData.isFlaggedForDeletion;
            }
        ),
        instanceDataCollection.end()
    );
}

const std::vector<Framework::Sprite::SpriteInstanceData> &Framework::Sprite::SpriteCollection::getInstanceData()
{
    if (frameCount > framesBetweenSpriteDeletion) {
        deleteInactiveSprites();
        frameCount = 0;
    }
    frameCount++;

    return instanceDataCollection;
}

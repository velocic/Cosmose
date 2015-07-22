#include <framework/sprite/spritecollection.h>

void Framework::Sprite::SpriteCollection::deleteInactiveSprites()
{
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

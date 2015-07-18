#include <framework/sprite/spritecollection.h>

void Framework::Sprite::SpriteCollection::deleteInactiveSprites()
{
    instanceDataCollection.erase(
        std::remove_if(
            instanceDataCollection.begin(),
            instanceDataColelction.end(),
            [](InstanceData &currentInstanceData) -> bool {
                if (currentInstanceData.isActive == false) {
                    return true;
                }
                return false;
            }
        ),
        instanceDataCollection.end()
    );
}

const std::vector<Framework::Sprite::SpriteInstanceData> &Framework::Sprite::SpriteCollection::getInstanceData() const
{
    if (frameCount > framesBetweenSpriteDeletion) {
        deleteInactiveSprites();
        frameCount = 0;
    }
    frameCount++;

    return instanceDataCollection;
}

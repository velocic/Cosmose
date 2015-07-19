#ifndef SPRITECOLLECTION_H
#define SPRITECOLLECTION_H

#include <framework/sprite/spriteinstancedata.h>
#include <opengl/texturecache.h>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace Framework
{
    namespace Sprite
    {
        class SpriteCollection
        {
            private:
                std::vector<SpriteInstanceData> instanceDataCollection;
                OpenGL::TextureCache &textureCache;
                std::string texturePath;
                unsigned int framesBetweenSpriteDeletion = 300;
                unsigned int frameCount = 0;
                void deleteInactiveSprites();
            public:
                //Note: texture at texturePath needs to be loaded from textureCache
                //before we can use it here. That way of working should be redesigned.
                SpriteCollection(
                    OpenGL::TextureCache &textureCache,
                    std::string texturePath
                ) :
                    textureCache(textureCache),
                    texturePath(texturePath)
                {}
                SpriteCollection(
                    OpenGL::TextureCache &textureCache,
                    std::string texturePath,
                    unsigned int framesBetweenSpriteDeletion
                ) :
                    textureCache(textureCache),
                    texturePath(texturePath),
                    framesBetweenSpriteDeletion(framesBetweenSpriteDeletion)
                {}
                const std::vector<SpriteInstanceData> &getInstanceData() const;
                template<typename SpriteType> std::unique_ptr<SpriteType> getSprite()
                {
                    InstanceData instanceData;
                    instanceDataCollection.push_back(instanceData);
                    return std::unique_ptr<SpriteType> spritePointer(
                        new SpriteType(
                            textureCache.get(texturePath),
                            instanceDataCollection.back()
                        )
                    );
                }
                template<typename SpriteType> std::unique_ptr<SpriteType> getSprite(SpriteType sourceSprite)
                {
                    InstanceData instanceData = sourceSprite.getInstanceData();
                    instanceDataCollection.push_back(instanceData);
                    return std::unique_ptr<SpriteType> spritePointer(
                        new SpriteType(
                            textureCache.get(texturePath),
                            instanceDataCollection.back()
                        )
                    );
                }
        }
    }
}

#endif

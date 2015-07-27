#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <framework/sprite/spriteinstancedata.h>
#include <framework/sprite/spriteinstancedataarray.h>
#include <opengl/texturecache.h>
#include <memory>
#include <string>

namespace Framework
{
    namespace Sprite
    {
        class SpriteManager
        {
            private:
                OpenGL::TextureCache &textureCache;
                std::string texturePath;
                SpriteInstanceDataArray instanceDataCollection;
            public:
                //Note: texture at texturePath needs to be loaded from textureCache
                //before we can use it here. That way of working should be redesigned.
                SpriteManager(
                    OpenGL::TextureCache &textureCache,
                    std::string texturePath,
                    unsigned int spriteCollectionMaxSize
                );
                const SpriteInstanceData *getInstanceData() const;
                template<typename SpriteType> std::unique_ptr<SpriteType> getSprite()
                {
                    std::unique_ptr<SpriteType> spritePointer(
                        new SpriteType(
                            textureCache.getTexture(texturePath),
                            instanceDataCollection.insert(),
                            instanceDataCollection
                        )
                    );
                    return spritePointer;
                }
                template<typename SpriteType> std::unique_ptr<SpriteType> getSprite(SpriteType sourceSprite)
                {
                    std::unique_ptr<SpriteType> spritePointer(
                        new SpriteType(
                            textureCache.getTexture(texturePath),
                            instanceDataCollection.insert(sourceSprite.getInstanceData()),
                            instanceDataCollection
                        )
                    );
                    return spritePointer;
                }
        };
    }
}

#endif

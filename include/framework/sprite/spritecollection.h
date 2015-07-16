#ifndef SPRITECOLLECTION_H
#define SPRITECOLLECTION_H

#include <framework/sprite/spriteinstancedata.h>
#include <opengl/texturecache.h>
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
            public:
                SpriteCollection();
                const std::vector<SpriteInstanceData> &getInstanceData() const;
                /*
                 * Template sprite creation function
                 * - return shared_ptr to sprite of typename T (so, any sprite)
                 * - assign it an ID, and create an entry for that ID in instanceDataCollection
                 * - pass it a reference to this class (i.e. sprite.parentCollection)
                 * - sprite d'tor should call a delete function here to remove its'
                 *   associated InstanceData. This should allow for game objects
                 *   to own sprites, and when those game objects go out of scope,
                 *   the sprites can destroy themselves and remove their instance data.
                 */
                void removeSpriteInstance(unsigned int instanceID);
        }
    }
}

#endif

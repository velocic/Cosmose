#ifndef BASICSPRITE_H
#define BASICSPRITE_H

#include <glm/gtc/matrix_transform.hpp>
#include <framework/sprite/spriteinstancedata.h>
#include <framework/sprite/spriteinstancedataarray.h>
#include <opengl/texture.h>
#include <memory>

namespace Framework
{
    namespace Sprite
    {
        class BasicSprite
        {
            private:
                std::weak_ptr<OpenGL::Texture> spriteTexture;
                SpriteInstanceDataArray &parentInstanceCollection;
            protected:
                SpriteInstanceData &instanceData;
            public:
                BasicSprite(
                    std::weak_ptr<OpenGL::Texture> spriteTexture,
                    SpriteInstanceData &instanceData,
                    SpriteInstanceDataArray &parentInstanceCollection
                );
                ~BasicSprite();
                const SpriteInstanceData &getInstanceData() const;
                std::weak_ptr<OpenGL::Texture> getTexture() const;
                void rotate(float rotationAngle, glm::vec3 rotationAxis);
                void scale(glm::vec3 scaleVector);
                void translate(glm::vec3 translationVector);
        };
    }
}

#endif

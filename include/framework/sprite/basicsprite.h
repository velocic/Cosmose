#ifndef BASICSPRITE_H
#define BASICSPRITE_H

#include <glm/gtc/matrix_transform.hpp>
#include <framework/sprite/spriteinstancedata.h>
#include <opengl/texture.h>
#include <memory>

namespace Framework
{
    namespace Sprite
    {
        class BasicSprite
        {
            private:
                std::shared_ptr<OpenGL::Texture> spriteTexture;
                SpriteInstanceData &instanceData;
            public:
                BasicSprite(
                    std::shared_ptr<OpenGL::Texture> spriteTexture,
                    SpriteInstanceData &instanceData
                );
                ~BasicSprite();
                const SpriteInstanceData &getInstanceData() const;
                std::shared_ptr<OpenGL::Texture> getTexture() const;
                void rotate(float rotationAngle, glm::vec3 rotationAxis);
                void scale(glm::vec3 scaleVector);
                void translate(glm::vec3 translationVector);
        };
    }
}

#endif

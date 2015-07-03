#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opengl/texture.h>
#include <memory>

namespace Framework
{
    class Sprite
    {
        private:
            std::shared_ptr<OpenGL::Texture> spriteTexture;
            glm::mat4 modelMatrix;
        public:
            Sprite(
                std::shared_ptr<OpenGL::Texture> spriteTexture,
                glm::mat4 modelMatrix
            ) : modelMatrix(modelMatrix),
                spriteTexture(spriteTexture) {}
            Sprite(
                std::shared_ptr<OpenGL::Texture> spriteTexture
            ) : spriteTexture(spriteTexture) {}
            glm::mat4 getModelMatrix();
            std::shared_ptr<OpenGL::Texture> getTexture();
            void rotate(float rotationAngle, glm::vec3 rotationAxis);
            void scale(glm::vec3 scaleVector);
            void translate(glm::vec3 translationVector);
    };
}

#endif

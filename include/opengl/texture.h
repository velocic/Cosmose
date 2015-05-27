#ifndef TEXTURE_H
#define TEXTURE_H

#include <gl3w.h>
#include <vector>

namespace OpenGL
{
    class Texture
    {
        private:
            GLuint textureID;
            int boundTextureUnit = -1;
        public:
            Texture(std::vector<uint8_t> &png);
            ~Texture();
            void bind(int textureUnit);
            void unbind();
            bool isBound();
            void setWrapMode(GLuint textureWrapS, GLuint textureWrapT);
            void setMinMagFilters(GLuint minFilter, GLuint magFilter);
    };
}

#endif

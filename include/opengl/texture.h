#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl3w.h>
#include <lodepng.h>
#include <string>
#include <vector>

namespace OpenGL
{
    class Texture
    {
        private:
            GLuint textureID;
            std::string textureName;
        public:
            Texture(std::vector<unsigned char> &rawPNG);
            ~Texture();
            void bind();
            std::string getName();
            void setName(std::string textureName);
            void setTextureParams(
                GLuint wrapModeS,
                GLuint wrapModeT,
                GLuint minFilter,
                GLuint magFilter,
                bool generateMipmap
            );
            void unbind();
    };
}

#endif

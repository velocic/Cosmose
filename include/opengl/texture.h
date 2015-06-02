#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl3w.h>
#include <vector>
#include <lodepng.h>

namespace OpenGL
{
    class Texture
    {
        private:
            GLuint textureID;
        public:
            Texture(std::vector<char> &rawPNG);
            ~Texture();
            void bind(int textureUnit);
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

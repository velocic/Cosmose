#ifndef TEXTURE_H
#define TEXTURE_H

#include <gl3w.h>
#include <vector>
#include <utilities/lodepng.h>

namespace OpenGL
{
    class Texture
    {
        private:
            GLuint textureID;
            bool isBound = false;
        public:
            Texture(
                std::vector<unsigned char> &rawPNG,
                int width,
                int height,
                GLuint wrapModeS,
                GLuint wrapModeT,
                GLuint minFilter,
                GLuint magFilter,
                bool generateMipmap
            );
            ~Texture();
            void bind(int textureUnit);
            void unbind();
            bool isBound();
            // void setWrapMode(GLuint textureWrapS, GLuint textureWrapT);
            // void setMinMagFilters(GLuint minFilter, GLuint magFilter);
    };
}

#endif

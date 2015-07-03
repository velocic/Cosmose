#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <GL/gl3w.h>
#include <opengl/texture.h>
#include <utilities/assetcache.h>
#include <memory>
#include <string>

namespace OpenGL
{
    class TextureCache
    {
        private:
            Utility::AssetCache<Texture> assetCache;
        public:
            TextureCache() {};
            std::shared_ptr<Texture> getTexture(std::string filePath);
            std::shared_ptr<Texture> loadTexture(
                std::string filePath,
                GLuint wrapModeS,
                GLuint wrapModeT,
                GLuint minFilter,
                GLuint magFilter,
                bool generateMipmap
            );
    };
}
#endif

#include <opengl/texturecache.h>

std::shared_ptr<Texture> OpenGL::TextureCache::getTexture(std::string filePath)
{
    return assetCache.get(filePath);
}

std::shared_ptr<Texture> OpenGL::TextureCache::loadTexture(
    std::string filePath,
    GLuint wrapModeS,
    GLuint wrapModeT,
    GLuint minFilter,
    GLuint magFilter,
    bool generateMipmap
)
{
    std::shared_ptr<Texture> texture = assetCache.get(filePath);
    texture->setTextureParams(
        wrapModeS,
        wrapModeT,
        minFilter,
        magFilter,
        generateMipmap
    );
    
    return texture;
}

#include <opengl/texture.h>

OpenGL::Texture::Texture(std::vector<unsigned char> &rawPNG)
{
    //use lodepng to decode the png data
    unsigned int width;
    unsigned int height;
    std::vector<unsigned char> decodedPNG;
    lodepng::decode(decodedPNG, width, height, rawPNG);

    //create texture buffer
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //pass the decoded image data to the texture buffer
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        decodedPNG.data()
    );

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGL::Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

void OpenGL::Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

std::string OpenGL::Texture::getName() const
{
    return textureName;
}

void OpenGL::Texture::setName(std::string textureName)
{
    this->textureName = textureName;
}

void OpenGL::Texture::setTextureParams(
    GLuint wrapModeS,
    GLuint wrapModeT,
    GLuint minFilter,
    GLuint magFilter,
    bool generateMipmap
)
{
    glBindTexture(GL_TEXTURE_2D, textureID);

    //configure the texture buffer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    if (generateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

#include <opengl/texture.h>

OpenGL::Texture::Texture(std::vector<uint8_t> &png, GLuint textureUnit)
{
    //create texture from png data
    glGenTextures(1, &textureID);
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //pass in the image data
    // glTexImage2D(, (GLvoid *)png.data());
}

OpenGL::Texture~Texture()
{
    //destroy texture
}

void OpenGL::Texture::bind()
{
    //bind to the specified texture unit
    //save the texture unit id for later
}

void OpenGL::Texture::unbind()
{
    //unbind the texture from the texture unit it is assigned to
    //set the texture unit id to -1
}

bool OpenGL::Texture::isBound()
{
    //return if the texture is currently bound, or not
}

void OpenGL::Texture::setWrapMode(GLuint textureWrapS, GLuint textureWrapT)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
}

void OpenGL::Texture::setMinMagFilters(GLuint minFilter, GLuint magFilter)
{
}

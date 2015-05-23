#include <opengl/context.h>

OpenGL::Context::Context(const Interface::Window &window)
{
    context = SDL_GL_CreateContext(window.getWindow());
}

OpenGL::Context::~Context()
{
    SDL_GL_DeleteContext(context);
}

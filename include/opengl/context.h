#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <interface/window.h>

namespace OpenGL
{
    class Context
    {
        private:
            SDL_GLContext context;
        public:
            Context(const Interface::Window &window);
            ~Context();
    };
}

#endif

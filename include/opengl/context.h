#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <UI/window.h>

namespace OpenGL
{
    class Context
    {
        private:
            SDL_GLContext context;
        public:
            Context(const UI::Window &window);
            ~Context();
    };
}

#endif

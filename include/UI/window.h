#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

namespace UI 
{
    class Window
    {
        private:
            SDL_Window* window;
            std::string title;
            int xPosition;
            int yPosition;
            int width;
            int height;
            Uint32 windowFlags;
        public:
            Window(
                std::string title,
                int xPosition,
                int yPosition,
                int width,
                int height,
                Uint32 windowFlags
            );
            ~Window();
            SDL_Window* getWindow() const;
    };
}

#endif

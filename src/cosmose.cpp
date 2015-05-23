#include <opengl/context.h>
#include <iostream>
#include <interface/window.h>
#include <SDL2/SDL.h>
#include <string>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    Interface::Window window(
        "Cosmose",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    SDL_Quit();
    return EXIT_SUCCESS;
}

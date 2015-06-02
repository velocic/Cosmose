#include <opengl/context.h>
#include <iostream>
#include <UI/window.h>
#include <SDL2/SDL.h>
#include <string>
#include <utilities/assetcache.h>
#include <opengl/texturecache.h>
#include <utilities/ioutils.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    UI::Window window(
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

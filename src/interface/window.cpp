#include <interface/window.h>

Interface::Window::Window(
    std::string title,
    int xPosition,
    int yPosition,
    int width,
    int height,
    Uint32 windowFlags
)
{
    this->title = title;
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->width = width;
    this->height = height;
    this->windowFlags = windowFlags;

    window = SDL_CreateWindow(
        title.c_str(),
        xPosition,
        yPosition,
        width,
        height,
        windowFlags
    );
}

Interface::Window::~Window()
{
    SDL_DestroyWindow(window);
}

SDL_Window* Interface::Window::getWindow()
{
    return window;
}

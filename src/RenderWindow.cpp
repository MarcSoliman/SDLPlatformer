#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
};

SDL_Texture *RenderWindow::LoadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {
        std::cout << "Failed to load a texture. Error: " << SDL_GetError() << std::endl;
    }

    return texture;
};

void RenderWindow::CleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::Clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::Render(SDL_Texture *p_tex)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 600;
    src.h = 600;

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 64;
    dst.h = 64;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::Display()
{
    SDL_RenderPresent(renderer);
}
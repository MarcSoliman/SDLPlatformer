#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"
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

void RenderWindow::Render(Entity &p_entity)
{
    SDL_Rect src;

    src.x = p_entity.GetCurrentFrame().x;
    src.y = p_entity.GetCurrentFrame().y;
    src.w = p_entity.GetCurrentFrame().w;

    SDL_Rect dst;
    dst.x = p_entity.GetPos().x;
    dst.y = p_entity.GetPos().y;
    dst.w = p_entity.GetCurrentFrame().w * 0.5;
    dst.h = p_entity.GetCurrentFrame().h * 0.5;

    SDL_RenderCopy(renderer, p_entity.GetTex(), &src, &dst);
}

void RenderWindow::Display()
{
    SDL_RenderPresent(renderer);
}
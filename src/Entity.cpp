#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
    : pos(p_pos), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 600;
    currentFrame.h = 600;
}

SDL_Texture *Entity::GetTex()
{
    return tex;
}

SDL_Rect Entity::GetCurrentFrame()
{
    return currentFrame;
}

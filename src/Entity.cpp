#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity(GLuint p_tex, Vector2f p_pos, Vector2f p_scale)
    : position(p_pos), scale(p_scale), tex(p_tex)
{
}

GLuint Entity::GetTex()
{
    return tex;
}

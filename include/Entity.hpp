#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Math.hpp>
#include <GL/glew.h>

class Entity
{
public:
    Entity(GLuint p_tex, Vector2f p_pos = Vector2f(0, 0), Vector2f p_scale = Vector2f(1, 1));
    Vector2f &GetPosition()
    {
        return position;
    }
    Vector2f &SetPosition(Vector2f p_pos)
    {
        position = p_pos;
    }
    Vector2f &GetScale()
    {
        return scale;
    }
    void SetScale(Vector2f p_scale)
    {
        scale = p_scale;
    }
    GLuint GetTex();

private:
    Vector2f position;
    Vector2f scale;
    GLuint tex;
};
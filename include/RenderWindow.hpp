#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include "Entity.hpp"
class RenderWindow
{
public:
    RenderWindow(const char *p_title, int p_w, int p_h);
    GLuint LoadTexture(const char *p_filePath);
    void CleanUp();
    void Clear();
    void Render(Entity &p_entity);
    void Display();

private:
    SDL_Window *window;
    SDL_GLContext glContext;
    GLuint shaderProgram;
};
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <GL/glew.h>

#include "Entity.hpp"
#include "RenderWindow.hpp"

const char *vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(inPos, 0.0, 1.0);
    texCoord = inTexCoord;



}
)";

const char *fragmentShaderSource = R"(
#version 330 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D spriteTexture;

void main()
{
    fragColor = texture(spriteTexture, texCoord);

    if(fragColor.a < 0.1)
    {
        discard;
    }




    //sunset
    //fragColor.r = fragColor.r * 0.393 + fragColor.g * 0.769 + fragColor.b * 0.189;

    //night time
    // fragColor.r = fragColor.r * 0.2 + fragColor.g * 0.686 + fragColor.b * 0.168;
    // fragColor.g = fragColor.r * 0.4 + fragColor.g * 0.534 + fragColor.b * 0.131;
    // fragColor.b = fragColor.r * 0.6 + fragColor.g * 0.769 + fragColor.b * 0.589;




}
)";

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), glContext(NULL)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        return;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        std::cout << "Failed to create OpenGL context. Error: " << SDL_GetError() << std::endl;
        return;
    }

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW. Error: " << glewGetErrorString(glewError) << std::endl;
        return;
    }

    shaderProgram = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex Shader compilation failed\n"
                  << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment Shader compilation failed\n"
                  << infoLog << std::endl;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Program linking failed\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint RenderWindow::LoadTexture(const char *p_filePath)
{
    SDL_Surface *surface = IMG_Load(p_filePath);
    if (!surface)
    {
        std::cout << "Failed to load a texture. Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    return textureID;
};

void RenderWindow::CleanUp()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}
void RenderWindow::Clear()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // For example, clear to dark gray
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderWindow::Render(Entity &p_entity)
{

    const int SCREEN_WIDTH = 1280; // your screen width
    const int SCREEN_HEIGHT = 720; // your screen height

    float normalizedWidth = 0.5f;
    float normalizedHeight = 0.5f;

    normalizedWidth *= p_entity.GetScale().x;
    normalizedHeight *= p_entity.GetScale().y;

    // Convert your entity's position from a top-left origin to normalized device coordinates.
    float normalizedX = (p_entity.GetPosition().x / SCREEN_WIDTH) * 2.0f - 1.0f;
    float normalizedY = 1.0f - (p_entity.GetPosition().y / SCREEN_HEIGHT) * 2.0f; // We flip the Y-axis here.

    float vertices[] = {
        normalizedX, normalizedY - normalizedHeight, 0.0f, 1.0f,                   // Bottom-left
        normalizedX + normalizedWidth, normalizedY - normalizedHeight, 1.0f, 1.0f, // Bottom-right
        normalizedX, normalizedY, 0.0f, 0.0f,                                      // Top-left
        normalizedX, normalizedY, 0.0f, 0.0f,                                      // Top-left again (for the triangle strip)
        normalizedX + normalizedWidth, normalizedY - normalizedHeight, 1.0f, 1.0f, // Bottom-right again
        normalizedX + normalizedWidth, normalizedY, 1.0f, 0.0f                     // Top-right
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, p_entity.GetTex());

    // Render the quad
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void RenderWindow::Display()
{
    SDL_GL_SwapWindow(window);
}
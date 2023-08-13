#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

int main(int argc, char *args[])
{

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init HAD FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
	}

	RenderWindow window("Game v1.0", 1280, 720);

	SDL_Texture *playerTexture = window.LoadTexture("res/gfx/mario.png");

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.Clear();
		window.Render(playerTexture);
		window.Display();
	}

	window.CleanUp();
	SDL_Quit();

	return 0;
}
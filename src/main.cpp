#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"

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
	SDL_Texture *platformTexture0 = window.LoadTexture("res/gfx/platform0.png");

	Entity player(Vector2f(0, 0), playerTexture);

	std::vector<Entity> platformEntityVector = {Entity(Vector2f(200, 5), platformTexture0),
												Entity(Vector2f(400, 5), platformTexture0)};

	bool gameRunning = true;

	SDL_Event event;
	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while (gameRunning)
	{
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep;

		window.Clear();
		for (Entity &platforms : platformEntityVector)
		{
			window.Render(platforms);
		}

		window.Render(player);

		window.Display();
	}

	window.CleanUp();
	SDL_Quit();

	return 0;
}
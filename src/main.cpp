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

	GLuint playerTexture = window.LoadTexture("res/gfx/mario.png");		   // Changed type to GLuint
	GLuint platformTexture0 = window.LoadTexture("res/gfx/platform0.png"); // Changed type to GLuint

	std::vector<Entity> platformEntityVector = {Entity(platformTexture0, Vector2f(0.0f, 60.0f)),
												Entity(platformTexture0, Vector2f(100.0f, 60.0f))};

	bool gameRunning = true;

	SDL_Event event;
	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	Entity player(playerTexture);
	player.SetScale(Vector2f(0.5, 1));

	int X = 0;

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

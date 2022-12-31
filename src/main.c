#include <stdio.h>
#include <stdbool.h>
#include "lib/lib.h"
#include "SDL3/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int
main()
{
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow(
				"SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOWEVENT_SHOWN
				);
		if(window == NULL)
		{
			printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);

			SDL_FillSurfaceRect(
					screenSurface,
					NULL,
					SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)
					);

			SDL_UpdateWindowSurface(window);

			SDL_Event e;
			bool quit = false;
			while(quit == false)
			{
				while(SDL_PollEvent(&e))
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	printf("number: %d\n", add(1, 3));
	printf("Hello World");

	return 0;
}

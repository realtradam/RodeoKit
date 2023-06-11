#pragma once

// -- external --
#include "SDL.h"
#include "SDL_syswm.h"

// -- system --
#include "inttypes.h"
#include "stdbool.h"

typedef
struct
{
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_SysWMinfo wmi;
	uint32_t width;
	uint32_t height;
	bool quit;
}
irodeo_window_state_t;

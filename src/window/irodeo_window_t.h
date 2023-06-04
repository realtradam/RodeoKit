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
	uint16_t screen_width;
	uint16_t screen_height;
	bool quit;
}
irodeo_window_state_t;

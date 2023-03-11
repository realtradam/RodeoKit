
// public internal
#include "rodeo_types.h"
#include "rodeo.h"

// external
#include "SDL/SDL.h"

int32_t
rodeo_input_mouse_x_get(void)
{
	int32_t x, y;
	SDL_GetMouseState(&x, &y);
	return x;
}

int32_t
rodeo_input_mouse_y_get(void)
{
	int32_t x, y;
	SDL_GetMouseState(&x, &y);
	return y;
}

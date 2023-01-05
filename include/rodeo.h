#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

typedef
struct
Rodeo__\
data_t
{
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_SysWMinfo wmi;
	int screen_width;
	int screen_height;
	SDL_Event sdl_event;
	bool quit;
} Rodeo__data_t;

typedef
struct
Rodeo__\
color_t
{
	float red;
	float green;
	float blue;
	float alpha;
} Rodeo__color_t;

void
Rodeo__\
init_window(
		Rodeo__data_t* state,
		int screen_height,
		int screen_width,
		char* title
		);

void
Rodeo__\
deinit_window(Rodeo__data_t* state);

void
Rodeo__\
quit();

void
Rodeo__\
begin(Rodeo__data_t* state);

void
Rodeo__\
end(Rodeo__data_t* state);

void
Rodeo__\
draw_debug_text(u_int16_t x, u_int16_t y, const char *format, ...);


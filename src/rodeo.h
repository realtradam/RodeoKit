#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

typedef
struct
Rodeo__\
Data_t
{
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_SysWMinfo wmi;
	int screen_width;
	int screen_height;
	SDL_Event sdl_event;
	bool quit;
} Rodeo__Data_t;

void
Rodeo__\
init_window(
		Rodeo__Data_t* state,
		int screen_height,
		int screen_width,
		char* title
		);

void
Rodeo__\
deinit_window(Rodeo__Data_t* state);

void
Rodeo__\
quit();

void
Rodeo__\
begin(Rodeo__Data_t* state);

void
Rodeo__\
end(Rodeo__Data_t* state);

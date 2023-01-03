#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"

#include "rodeo.h"

Rodeo__Data_t _state = {0};
Rodeo__Data_t* state = &_state;

int
main()
{
	Rodeo__init_window(state, 480, 640, "Rodeo Window");

	while(!state->quit)
	{
		Rodeo__begin(state);

		bgfx_dbg_text_printf(0, 2, 0x6f, "Description: Initialization and debug text.");

		Rodeo__end(state);
	}

	Rodeo__deinit_window(state);
	Rodeo__quit();
	return 0;
}

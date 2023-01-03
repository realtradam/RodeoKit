#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"

#include "rodeo.h"

//static Rodeo__Data_t Rodeo__State = { 0 };

void
Rodeo__\
init_window(
		Rodeo__Data_t* state,
		int screen_height,
		int screen_width,
		char* title
		)
{
	state->window = NULL;
	state->screen_surface = NULL;
	state->screen_height = screen_height;
	state->screen_width = screen_width;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	state->window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN
			);

	if(state->window == NULL)
	{
		printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_VERSION(&state->wmi.version);
	if(
			!SDL_GetWindowWMInfo(
				state->window,
				&state->wmi
				)
	  )
	{
		printf("SDL_Error %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	bgfx_render_frame(-1);

	bgfx_platform_data_t pd;
	memset(&pd, 0, sizeof(bgfx_platform_data_t));

	pd.ndt = state->wmi.info.x11.display;
	pd.nwh = (void*)(uintptr_t)state->wmi.info.x11.window;

	bgfx_init_t init = {0};
	bgfx_init_ctor(&init);
	init.type = BGFX_RENDERER_TYPE_COUNT; // auto determine renderer
	init.resolution.width = state->screen_width;
	init.resolution.height = state->screen_height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.platformData = pd;
	bgfx_init(&init);

	bgfx_reset(state->screen_width, state->screen_height, BGFX_RESET_VSYNC, init.resolution.format);

	bgfx_set_debug(BGFX_DEBUG_TEXT);

	bgfx_set_view_clear(
			0,
			BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
			0x443355FF,
			1.0f,
			0
			);
	bgfx_set_view_rect(0, 0, 0, state->screen_width, state->screen_height);

	bgfx_touch(0);

	bgfx_frame(false);
}

void
Rodeo__\
deinit_window(Rodeo__Data_t* state)
{
	bgfx_shutdown();
	SDL_DestroyWindow(state->window);
}

void
Rodeo__\
quit()
{
	SDL_Quit();
}

void
Rodeo__\
begin(Rodeo__Data_t* state)
{
}

void
Rodeo__\
end(Rodeo__Data_t* state)
{
	while(SDL_PollEvent(&state->sdl_event))
	{
		if(state->sdl_event.type == SDL_QUIT)
		{
			state->quit = true;
		}
	}
	bgfx_touch(0);
	bgfx_frame(false);
}

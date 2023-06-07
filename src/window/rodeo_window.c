
// -- internal --
// public
#include "rodeo/window.h"
#include "rodeo/log.h"
// private
#include "window/irodeo_window.h"

// -- external --
#include "SDL.h"
#include "stc/cstr.h"

static irodeo_window_state_t irodeo_window_state = {0};

void
rodeo_window_init(
	uint16_t screen_height,
	uint16_t screen_width,
	cstr title
)
{
	irodeo_window_state.window = NULL;
	irodeo_window_state.screen_surface = NULL;
	irodeo_window_state.screen_height = screen_height;
	irodeo_window_state.screen_width = screen_width;

	rodeo_log(
		rodeo_logLevel_info,
		"Initializing SDL..."
	);

	{
		uint32_t init_flags_sdl = 0;
		init_flags_sdl = init_flags_sdl | SDL_INIT_VIDEO;
		init_flags_sdl = init_flags_sdl | SDL_INIT_AUDIO;
		init_flags_sdl = init_flags_sdl | SDL_INIT_GAMECONTROLLER;
	
		if(SDL_Init(init_flags_sdl) < 0)
		{
			rodeo_log(
				rodeo_logLevel_error,
				"Failed to initialize SDL. SDL_Error: %s",
				SDL_GetError()
			);
			exit(EXIT_FAILURE);
		}
		rodeo_log(
			rodeo_logLevel_info,
			"Success initializing SDL"
		);
	}

	rodeo_log(
		rodeo_logLevel_info,
		"Initializing SDL window..."
	);
	irodeo_window_state.window = SDL_CreateWindow(
			cstr_str(&title),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN //| SDL_WINDOW_RESIZABLE
			);
	if(irodeo_window_state.window == NULL)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed creating SDL window. SDL_Error: %s",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_logLevel_info,
		"Success initializing SDL window"
	);

#if !__EMSCRIPTEN__
	rodeo_log(
		rodeo_logLevel_info,
		"SDL setting up driver specific information..."
	);
	SDL_VERSION(&irodeo_window_state.wmi.version);
	if(
		!SDL_GetWindowWMInfo(
			irodeo_window_state.window,
			&irodeo_window_state.wmi  
		)
	)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"SDL failed to get driver specific information. SDL Error: %s", SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_logLevel_info,
		"Success getting driver specific information"
	);
#endif
}

void
rodeo_window_deinit(void)
{
	SDL_DestroyWindow(irodeo_window_state.window);
	SDL_Quit();
}

void
irodeo_window_update_screen_size(void)
{
	int32_t width = 0;
	int32_t height = 0;
	SDL_GetWindowSize(
		irodeo_window_state.window,
		&width,
		&height
	);
	irodeo_window_state.screen_width = (uint32_t)width;
	irodeo_window_state.screen_height = (uint32_t)height;
}

uint32_t
rodeo_window_screen_width_get(void)
{
	irodeo_window_update_screen_size();
	return irodeo_window_state.screen_width;
}

uint32_t
rodeo_window_screen_height_get(void)
{
	irodeo_window_update_screen_size();
	return irodeo_window_state.screen_height;
}

void
irodeo_window_screen_width_setVar(uint16_t width)
{
	irodeo_window_state.screen_width = width;
}

void
irodeo_window_screen_height_setVar(uint16_t height)
{
	irodeo_window_state.screen_height = height;
}

bool
rodeo_window_shouldQuit(void)
{
	return irodeo_window_state.quit;
}

void
rodeo_window_quit(void)
{
	irodeo_window_state.quit = true;
}

SDL_Window *
irodeo_window_get(void)
{
	return irodeo_window_state.window;
}

SDL_Surface *
irodeo_window_surface_get(void)
{
	return irodeo_window_state.screen_surface;
}

SDL_SysWMinfo
irodeo_window_wmi_get(void)
{
	return irodeo_window_state.wmi;
}


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
	uint32_t width,
	uint32_t height,
	cstr title
)
{
	irodeo_window_state.window = NULL;
	irodeo_window_state.screen_surface = NULL;
	irodeo_window_state.height = height;
	irodeo_window_state.width = width;

	rodeo_log(
		rodeo_logLevel_info,
		"Initializing SDL Video..."
	);

	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to initialize SDL Video. SDL_Error: %s",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_logLevel_info,
		"Success initializing SDL Video"
	);

	rodeo_log(
		rodeo_logLevel_info,
		"Initializing SDL window..."
	);
	irodeo_window_state.window = SDL_CreateWindow(
			cstr_str(&title),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			(int32_t)width,
			(int32_t)height,
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
irodeo_window_dimensions_update(void)
{
	int32_t width = 0;
	int32_t height = 0;
	SDL_GetWindowSize(
		irodeo_window_state.window,
		&width,
		&height
	);
	irodeo_window_state.width = (uint32_t)width;
	irodeo_window_state.height = (uint32_t)height;
}

uint32_t
rodeo_window_width_get(void)
{
	//irodeo_window_update_screen_size();
	return irodeo_window_state.width;
}

uint32_t
rodeo_window_height_get(void)
{
	//irodeo_window_update_screen_size();
	return irodeo_window_state.height;
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

uint64_t
rodeo_window_elapsedTime_ms(void)
{
	return SDL_GetTicks64();
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

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"

#include "rodeo_types.h"


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

const char *
Rodeo__\
get_renderer_name_as_string();

void
Rodeo__\
flush_batch(Rodeo__data_t *state);

void
Rodeo__\
draw_rectangle(
	Rodeo__data_t *state,
	u_int16_t x,
	u_int16_t y,
	u_int16_t width,
	u_int16_t height,
	struct Rodeo__color_rgba_t color
);

bgfx_shader_handle_t
Rodeo__\
load_shader(const char* path);

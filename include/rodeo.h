
// public internal
#include "rodeo_types.h"

// system
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>



void
Rodeo__\
init_window(
	Rodeo__data_p *state,
	int screen_height,
	int screen_width,
	char* title
);

void
Rodeo__\
deinit_window(Rodeo__data_p state);

void
Rodeo__\
quit();

void
Rodeo__\
begin(Rodeo__data_p state);

void
Rodeo__\
end(Rodeo__data_p state);

bool
Rodeo__\
should_quit(Rodeo__data_p state);

void
Rodeo__\
draw_debug_text(uint16_t x, uint16_t y, const char *format, ...);

const char *
Rodeo__\
get_renderer_name_as_string();

void
Rodeo__\
flush_batch(Rodeo__data_p state);

void
Rodeo__\
draw_rectangle(
	Rodeo__data_p state,
	uint16_t x,
	uint16_t y,
	uint16_t width,
	uint16_t height,
	Rodeo__color_rgba_t color
);


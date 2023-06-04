#pragma once

// -- internal --
// public
//#include "rodeo/window_t.h"

// -- external --
#include "stc/cstr.h"

// -- system --
#include <inttypes.h>


void
rodeo_window_init(
	uint16_t screen_height,
	uint16_t screen_width,
	cstr title
);

void
rodeo_window_deinit(void);

uint16_t
rodeo_window_screen_width_get(void);

uint16_t
rodeo_window_screen_height_get(void);

bool
rodeo_window_shouldQuit(void);

void
rodeo_window_quit(void);

#define								\
mrodeo_window_do(					\
	screen_height,					\
	screen_width,					\
	title							\
)									\
	mrodeo_defer_do(				\
		rodeo_window_init(			\
			screen_height,			\
			screen_width,			\
			title					\
		),							\
		rodeo_window_deinit()		\
	)


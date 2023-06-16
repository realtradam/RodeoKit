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
	uint32_t screen_height,
	uint32_t screen_width,
	cstr title
);

void
rodeo_window_deinit(void);

uint32_t
rodeo_window_width_get(void);

uint32_t
rodeo_window_height_get(void);

bool
rodeo_window_shouldQuit(void);

void
rodeo_window_quit(void);

#define								\
mrodeo_window_do(					\
	screen_width,					\
	screen_height,					\
	title							\
)									\
	mrodeo_defer_do(				\
		rodeo_window_init(			\
			screen_width,			\
			screen_height,			\
			title					\
		),							\
		rodeo_window_deinit()		\
	)


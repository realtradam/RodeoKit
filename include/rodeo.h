
// public internal
#include "rodeo_types.h"

// system
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define mrodeo_name_concat(prefix, suffix) prefix##suffix
#define mrodeo_macrovar(prefix) mrodeo_name_concat(prefix##_, __LINE__)

#define mrodeo_defer_do(start, end) for(				\
		int mrodeo_macrovar(_macrovar_) = (start, 0);	\
		!mrodeo_macrovar(_macrovar_);					\
		(mrodeo_macrovar(_macrovar_) += 1), end)			\

/// --- Math ---

uint32_t
rodeo_rgba_to_uint32(const rodeo_rgba_t color);

/// --- Core ---

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
		rodeo_window_deinit()			\
	)

void
rodeo_window_init(
	int screen_height,
	int screen_width,
	char* title
);

void
rodeo_window_deinit(void);

#define						\
mrodeo_frame_do(					\
	state					\
)							\
	mrodeo_defer_do(		\
		rodeo_frame_begin(state),	\
		rodeo_frame_end(state)	\
	)

void
rodeo_frame_begin(void);

void
rodeo_frame_end(void);

void
rodeo_mainloop_run(
	rodeo_mainloop_func main_loop_function
);

bool
rodeo_window_check_quit(void);

void
rodeo_set_quit(bool quit);

void
rodeo_debug_text_draw(uint16_t x, uint16_t y, const char *format, ...);

rodeo_string_p
rodeo_renderer_name_get(void);

void
rodeo_renderer_flush(void);

void
rodeo_rectangle_draw(
	rodeo_rectangle_t rectangle,
	rodeo_rgba_t color
);

/// --- String ---

rodeo_string_p
rodeo_string_create(const char *c_string);

void
rodeo_string_destroy(rodeo_string_p self);

char*
rodeo_string_to_cstr(rodeo_string_p self);

const char*
rodeo_string_to_constcstr(rodeo_string_p self);

void
rodeo_string_insert(
	rodeo_string_p self,
	const rodeo_string_p insert,
	intptr_t position
);

void
rodeo_string_append(
	rodeo_string_p self,
	const rodeo_string_p append
);

void
rodeo_string_prepend(
	rodeo_string_p self,
	const rodeo_string_p prepend
);

void
rodeo_string_clear(rodeo_string_p self);

void
rodeo_string_set(rodeo_string_p self, char* value);


// -- internal --
// public
#include "rodeo_types.h"

// system
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#define mrodeo_name_concat(prefix, suffix) prefix##suffix

#define mrodeo_macrovar(prefix) mrodeo_name_concat(prefix##_, __LINE__)

#define mrodeo_defer_do(start, end)						\
	for(												\
		int mrodeo_macrovar(_macrovar_) = (start, 0);	\
		!mrodeo_macrovar(_macrovar_);					\
		(mrodeo_macrovar(_macrovar_) += 1), end			\
	)													\

#define								\
mrodeo_vargs_do(final_arg)			\
	va_list vargs;					\
	mrodeo_defer_do(				\
		va_start(vargs, final_arg),	\
		va_end(vargs)				\
	)								\

/// --- Math ---

rodeo_RGBA8_t
rodeo_RGBAFloat_to_RGBA8(const rodeo_RGBAFloat_t color);

rodeo_BGRA8_t
rodeo_RGBA8_to_BGRA8(const rodeo_RGBA8_t color);
/// --- Core ---

extern rodeo_texture_2d_t rodeo_texture_2d_default;

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

void
rodeo_window_init(
	int screen_height,
	int screen_width,
	char* title
);

void
rodeo_window_deinit(void);

#define								\
mrodeo_frame_do(					\
	state							\
)									\
	mrodeo_defer_do(				\
		rodeo_frame_begin(state),	\
		rodeo_frame_end(state)		\
	)

void
rodeo_frame_begin(void);

void
rodeo_frame_end(void);

void
rodeo_mainloop_run(
	rodeo_mainLoop_function main_loop_func
);

bool
rodeo_window_check_quit(void);

void
rodeo_set_quit(bool quit);

void
rodeo_debug_text_draw(uint16_t x, uint16_t y, const char *format, ...);

rodeo_string_t
rodeo_renderer_name_get(void);

void
rodeo_renderer_flush(void);

void
rodeo_rectangle_draw(
	rodeo_rectangle_t rectangle,
	rodeo_RGBAFloat_t color
);

rodeo_texture_2d_t
rodeo_texture_2d_create_from_RGBA8(
	const uint32_t width,
	const uint32_t height,
	const uint8_t memory[]
);

void
rodeo_texture_2d_draw(
	const rodeo_rectangle_t source,
	const rodeo_rectangle_t destination,
	const rodeo_RGBAFloat_t color,
	const rodeo_texture_2d_t *texture
);

/// --- String ---

rodeo_string_t
rodeo_string_create(const char *c_string);

void
rodeo_string_destroy(rodeo_string_t *self);

char*
rodeo_string_to_cstr(rodeo_string_t *self);

const char*
rodeo_string_to_constcstr(const rodeo_string_t *self);

void
rodeo_string_insert(
	rodeo_string_t *self,
	const rodeo_string_t insert,
	intptr_t position
);

void
rodeo_string_append(
	rodeo_string_t *self,
	const rodeo_string_t append
);

void
rodeo_string_prepend(
	rodeo_string_t *self,
	const rodeo_string_t prepend
);

void
rodeo_string_clear(rodeo_string_t *self);

void
rodeo_string_set(rodeo_string_t *self, char *value);

rodeo_string_t
rodeo_string_clone(const rodeo_string_t self);

rodeo_string_t
rodeo_string_format(const char *format, ...);

rodeo_string_t
rodeo_string_vargs_format(const char *format, va_list vargs);

/// --- Log ---

void
rodeo_log(
	rodeo_loglevel_t loglevel,
	const char *format,
	...
);

/// --- Framerate ---

uint64_t
rodeo_frame_count_get(void);

float
rodeo_frame_time_get(void);

float
rodeo_frame_persecond_get(void);

void
rodeo_frame_limit_set(uint32_t limit);

uint32_t
rodeo_frame_limit_get(void);

/// --- Input ---

int32_t
rodeo_input_mouse_x_get(void);

int32_t
rodeo_input_mouse_y_get(void);

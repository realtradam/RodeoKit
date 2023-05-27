
// -- internal --
// public
#include "rodeo_types.h"
#include "rodeo/input.h"
#include "rodeo/log.h"
#include "rodeo/common.h"
#include "rodeo/audio.h"
#include "rodeo/collision.h"

// -- external --
#include "stc/cstr.h"

// -- system --
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

/// --- Math ---

rodeo_color_RGBA8_t
rodeo_color_RGBAFloat_to_RGBA8(const rodeo_color_RGBAFloat_t color);

rodeo_color_RGBAFloat_t
rodeo_color_RGBA8_to_RGBAFloat(const rodeo_color_RGBA8_t color);

void
rodeo_random_seed_set(uint64_t seed);

double
rodeo_random_double_get(void);

uint64_t
rodeo_random_uint64_get(void);

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
		rodeo_window_deinit()		\
	)

void
rodeo_window_init(
	uint16_t screen_height,
	uint16_t screen_width,
	cstr title
);

void
rodeo_window_deinit(void);

uint16_t
rodeo_screen_width_get(void);

uint16_t
rodeo_screen_height_get(void);

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
rodeo_mainLoop_run(
	rodeo_mainLoop_function main_loop_func
);

bool
rodeo_window_quit_get(void);

void
rodeo_window_quit_set(bool quit);

void
rodeo_debug_text_draw(uint16_t x, uint16_t y, const char *format, ...);

cstr
rodeo_renderer_name_get(void);

void
rodeo_renderer_flush(void);

const rodeo_texture_2d_t*
rodeo_texture_2d_default_get(void);

rodeo_texture_2d_t
rodeo_texture_2d_create_from_RGBA8(
	const uint16_t width,
	const uint16_t height,
	const uint8_t memory[]
);

rodeo_texture_2d_t
rodeo_texture_2d_create_from_path(cstr path);

void
rodeo_texture_2d_destroy(rodeo_texture_2d_t *texture);

void
rodeo_rectangle_draw(
	const rodeo_rectangle_t *rectangle,
	const rodeo_color_RGBAFloat_t *color
);

void
rodeo_texture_2d_draw(
	const rodeo_rectangle_t *destination,
	const rodeo_rectangle_t *source,
	const rodeo_color_RGBAFloat_t *color,
	const rodeo_texture_2d_t *texture
);


/// --- Framerate ---

uint64_t
rodeo_frame_count_get(void);

float
rodeo_frame_time_get(void);

float
rodeo_frame_perSecond_get(void);

void
rodeo_frame_limit_set(uint32_t limit);

uint32_t
rodeo_frame_limit_get(void);

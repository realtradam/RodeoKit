
// -- internal --
// public
#include "rodeo_types.h"
#include "rodeo/input.h"
#include "rodeo/log.h"
#include "rodeo/common.h"
#include "rodeo/audio.h"
#include "rodeo/collision.h"
#include "rodeo/gfx.h"
#include "rodeo/window.h"

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

void
rodeo_mainLoop_run(
	rodeo_mainLoop_function main_loop_func
);

void
rodeo_debug_text_draw(uint16_t x, uint16_t y, const char *format, ...);


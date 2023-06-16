
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
#include "rodeo/math.h"

// -- system --
#include <stdint.h>

/// --- Math ---

rodeo_color_RGBA8_t
rodeo_color_RGBAFloat_to_RGBA8(const rodeo_color_RGBAFloat_t color);

rodeo_color_RGBAFloat_t
rodeo_color_RGBA8_to_RGBAFloat(const rodeo_color_RGBA8_t color);

/// --- Core ---

void
rodeo_mainLoop_run(
	rodeo_mainLoop_function main_loop_func
);

void
rodeo_debug_text_draw(uint16_t x, uint16_t y, const char *format, ...);

// intialize all subsystems
void
rodeo_init(float width, float height, cstr window_name, uint32_t audio_channels);

// deintialize all subsystems
void
rodeo_deinit(void);

// macro to intialize/deinitialize all subsystems
#define \
mrodeo_do(width, height, window_name, audio_channels) \
	mrodeo_defer_do( \
		rodeo_init(width, height, window_name, audio_channels), \
		rodeo_deinit() \
	)

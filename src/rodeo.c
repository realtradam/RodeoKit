
// -- internal --
// public
#include "rodeo.h"
#include "rodeo_types.h"

// -- external --
#if __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif
#include "bgfx/c99/bgfx.h"

// -- system --
#include <time.h>
#include <inttypes.h>

// intialize all subsystems
void
rodeo_init(float width, float height, cstr window_name, uint32_t audio_channels)
{
	rodeo_window_init((uint32_t)width, (uint32_t)height, window_name);
	rodeo_input_init();
	rodeo_math_rng_init();
	rodeo_audio_init(audio_channels);
	rodeo_gfx_init(width, height);
}

// deintialize all subsystems
void
rodeo_deinit(void)
{
	rodeo_gfx_deinit();
	rodeo_audio_deinit();
	rodeo_math_rng_deinit();
	rodeo_input_deinit();
	rodeo_window_deinit();
}

void
rodeo_mainLoop_run(
	rodeo_mainLoop_function main_loop_func
)
{
	#if __EMSCRIPTEN__
		emscripten_set_main_loop(main_loop_func, 0, 1);
	#else
		while(!rodeo_window_shouldQuit())
		{ 
			main_loop_func();
		} 
	#endif
}

void
rodeo_debug_text_draw(uint16_t x, uint16_t y, const char *format, ...)
{
	mrodeo_vargs_do(format)
	{
		bgfx_dbg_text_vprintf(x, y, 0x65, format, vargs);
	}
}


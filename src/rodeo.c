
// -- internal --
// public
#include "rodeo.h"
#include "rodeo_types.h"
// private
#include "rodeo_internal.h"
#include "rodeo_internal_types.h"

// -- external --
#if __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_syswm.h"
#include "SDL.h"
#include "bgfx/c99/bgfx.h"
/*#define CGLM_FORCE_LEFT_HANDED*/
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
/*#define CGLM_CLIPSPACE_INCLUDE_ALL*/
#include "cglm/cglm.h"
#include "stc/crandom.h"

// -- system --
#include <time.h>
#include <inttypes.h>

static irodeo_state_t state = {0};

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
rodeo_debug_text_draw(u_int16_t x, u_int16_t y, const char *format, ...)
{
	mrodeo_vargs_do(format)
	{
		bgfx_dbg_text_vprintf(x, y, 0x65, format, vargs);
	}
}

void
irodeo_random_seed_set(stc64_t seed)
{
	state.random_seed = seed;
}

stc64_t*
irodeo_random_seed_get(void)
{
	return &state.random_seed;
}


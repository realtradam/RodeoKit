#pragma once

// -- internal --
// public
#include "rodeo_config.h"
#include "rodeo_types.h"

// -- external --
#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
#endif
#include "SDL.h"
#include "SDL_syswm.h"
#include "bgfx/c99/bgfx.h"
#include "stc/crandom.h"
/*#define CGLM_FORCE_LEFT_HANDED*/
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
/*#define CGLM_CLIPSPACE_INCLUDE_ALL*/
#include "cglm/cglm.h"

typedef struct
{
	stc64_t random_seed;

	uint64_t frame_count;
	uint32_t frame_limit;
}
irodeo_state_t;

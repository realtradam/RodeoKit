#pragma once

// -- external --
#include "stc/cstr.h"

// -- system --
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef
void
(*rodeo_mainLoop_function)(void);

typedef
struct
{
	float x;
	float y;
	float width;
	float height;
}
rodeo_rectangle_t;

/*
typedef struct
{
	rodeo_texture_2d_t texture;
	rodeo_frameBuffer_internal_p internal_frame_buffer;
}
rodeo_frameBuffer_2d_t;
*/


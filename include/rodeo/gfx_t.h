#pragma once

// -- internal --
// public
#include "rodeo_types.h"
#include "rodeo/math/vec2_t.h"
// -- system --
#include <inttypes.h>

typedef struct irodeo_gfx_texture_2d irodeo_gfx_texture_2d_t;

typedef
struct
{
	irodeo_gfx_texture_2d_t *data;
	uint32_t width;
	uint32_t height;
}
rodeo_gfx_texture_2d_t;

typedef
union
{
	struct
	{
		float red;
		float green;
		float blue;
		float alpha;
	}
	colors;
	float array[4];
}
rodeo_color_RGBAFloat_t;

typedef
union
{
	struct
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	}
	colors;
	uint32_t rgba;
	uint8_t array[4];
}
rodeo_color_RGBA8_t;

typedef
struct
{
	float x;
	float y;
	float z;
	rodeo_color_RGBAFloat_t color;
	//float red;
	//float green;
	//float blue;
	//float alpha;
	float texture_x;
	float texture_y;
	float texture_id;
}
rodeo_gfx_vertex_t;

typedef uint16_t rodeo_gfx_index_t;

typedef
struct
{
	rodeo_math_vec2_t target;
	float turns;
	float zoom;
	rodeo_math_vec2_t offset;
}
rodeo_gfx_camera_2d_t;


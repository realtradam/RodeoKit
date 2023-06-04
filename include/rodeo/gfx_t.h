#pragma once

// -- internal --
// public
#include "rodeo_types.h"
// -- system --
#include <inttypes.h>

typedef struct irodeo_gfx_texture_internal irodeo_gfx_texture_internal_t;

typedef
struct
{
	irodeo_gfx_texture_internal_t *internal_texture;
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

#pragma once

// -- external --
#include "stc/cstr.h"

// -- system --
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct irodeo_texture_internal_t irodeo_texture_internal_t;
typedef irodeo_texture_internal_t *rodeo_texture_internal_p;

typedef
union
{
	struct {
		float red;
		float green;
		float blue;
		float alpha;
	};
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
	};
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
rodeo_vertex_t;

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

typedef
struct
{
	rodeo_texture_internal_p internal_texture;
	uint32_t width;
	uint32_t height;
}
rodeo_texture_2d_t;

/*
typedef struct
{
	rodeo_texture_2d_t texture;
	rodeo_frameBuffer_internal_p internal_frame_buffer;
}
rodeo_frameBuffer_2d_t;
*/


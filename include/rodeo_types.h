#pragma once

// system
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

/// --- String ---

// taken from STC library
// must match their layout exactly as it will be cast to it.
// (TODO should write test cases for the string funcs)
typedef char rodeo_string_value_t;
typedef struct { rodeo_string_value_t* data; intptr_t size, cap; } rodeo_string_buffer_t;
typedef union {
    struct { rodeo_string_value_t data[sizeof(rodeo_string_buffer_t) - 1]; unsigned char size; } sml;
    struct { rodeo_string_value_t* data; size_t size, ncap; } lon;
} rodeo_string_t;

/// --- Log ---

typedef
enum
{
	rodeo_logLevel_info,
	rodeo_logLevel_warning,
	rodeo_logLevel_error
}
rodeo_logLevel_t;

typedef
void
(*rodeo_log_function)(rodeo_string_t text);

typedef 
union
{
	struct {
		float x;
		float y;
	};
	float array[2];
}
rodeo_vector2_t;

typedef 
union
{
	struct {
		float x;
		float y;
		float z;
	};
	float array[3];
}
rodeo_vector3_t;

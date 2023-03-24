#pragma once

// system
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct
{
	float red;
	float green;
	float blue;
	float alpha;
}
rodeo_rgba_t;

typedef struct
{
	float x;
	float y;
	float z;
	uint32_t abgr;
	float tex_x;
	float tex_y;
}
rodeo_vertex_t;

typedef
void
(*rodeo_mainloop_function)(void);

typedef struct
{
	float x;
	float y;
	float width;
	float height;
}
rodeo_rectangle_t;

typedef struct
{
	uint8_t fill_this_out;
}
rodeo_texture_2d_t;

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

typedef enum
{
	rodeo_loglevel_info,
	rodeo_loglevel_warning,
	rodeo_loglevel_error
}
rodeo_loglevel_t;

typedef
void
(*rodeo_log_function)(rodeo_string_t text);

typedef rodeo_texture_2d_t* rodeo_texture_2d_p;

#pragma once

// system
#include <stdbool.h>
#include <stdint.h>

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
}
rodeo_vertex_t;

typedef
void
(*rodeo_mainloop_func)(void);

typedef struct
{
	float x;
	float y;
	float width;
	float height;
}
rodeo_rectangle_t;

typedef union rodeo_string_t *rodeo_string_p;

#pragma once

// system
#include <stdbool.h>
#include <stdint.h>

typedef
struct
Rodeo__\
color_rgba
{
	float red;
	float green;
	float blue;
	float alpha;
}
Rodeo__\
color_rgba_t;

typedef
struct
Rodeo__position_color_vertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
}
Rodeo__\
position_color_vertex_t;

typedef
struct
Rodeo__data
*Rodeo__\
data_p;

typedef
void
(*Rodeo__\
main_loop_p)
(void);

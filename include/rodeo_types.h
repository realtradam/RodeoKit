#pragma once

// system
#include <stdbool.h>
#include <stdint.h>

typedef
struct
{
	float red;
	float green;
	float blue;
	float alpha;
}
rodeo_\
rgba_t;

typedef
struct
{
	float x;
	float y;
	float z;
	uint32_t abgr;
}
rodeo_\
position_color_vertex_t;
//rodeo_poscolvert_t

typedef
struct
rodeo_data_t
*rodeo_data_p;

typedef
void
(*rodeo_\
mainloop_func)
(void);

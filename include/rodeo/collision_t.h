#pragma once

// -- system --
#include <stdint.h>
#include <stdbool.h>

typedef
struct
{
	uint32_t id;
	float x;
	float y;
	float dx;
	float dy;
	bool is_circle;
	float width;
	float height;
}
rodeo_collision_2d_world_item_t;

int rodeo_collision_2d_item_cmp(
	const rodeo_collision_2d_world_item_t* a,
	const rodeo_collision_2d_world_item_t* b
);

#define i_val rodeo_collision_2d_world_item_t
#define i_cmp rodeo_collision_2d_item_cmp
#define i_type cvec_collision_2d_world_item
#include "stc/cvec.h"

typedef cvec_collision_2d_world_item rodeo_collision_2d_world_t;

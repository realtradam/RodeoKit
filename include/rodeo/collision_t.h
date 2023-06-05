#pragma once

// -- internal --
// public
#include "rodeo_types.h"

// -- system --
#include <stdint.h>
#include <stdbool.h>

struct cvec_collision_2d_world_item;

typedef
struct
{
	uint32_t id;
    struct cvec_collision_2d_world_item  *world;
} world_id;

typedef
struct
{
    world_id id;
	rodeo_rectangle_t rect;
	float dx;
	float dy;
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

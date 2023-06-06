#pragma once

// -- internal --
// public
#include "rodeo_types.h"

// -- system --
#include <stdint.h>
#include <stdbool.h>

typedef struct rodeo_collision_2d_item rodeo_collision_2d_item_t;
typedef struct rodeo_collision_2d_collection_data rodeo_collision_2d_collection_data_t;
typedef struct rodeo_collision_2d_item_data rodeo_collision_2d_item_data_t;

typedef 
struct 
rodeo_collision_2d_collection
{
	rodeo_collision_2d_collection_data_t *data;
}
rodeo_collision_2d_collection_t;

typedef
struct
{
	//uint32_t id;
    rodeo_collision_2d_collection_t collection;
	rodeo_collision_2d_item_data_t **self_handle; // needs to be updated automatically whenever it moves in the struct
}
rodeo_collision_2d_item_id_t;

struct
rodeo_collision_2d_item_data
{
    rodeo_collision_2d_item_id_t id;
	rodeo_rectangle_t rect;
	float dx;
	float dy;
};

struct
rodeo_collision_2d_item
{
	rodeo_collision_2d_item_data_t **data_handle;
};

int32_t irodeo_collision_2d_item_data_cmp(
	const rodeo_collision_2d_item_data_t *a,
	const rodeo_collision_2d_item_data_t *b
);

#define i_val rodeo_collision_2d_item_data_t
#define i_cmp irodeo_collision_2d_item_data_cmp
#define i_type cvec_collision_2d_item_data
#include "stc/cvec.h"

struct
rodeo_collision_2d_collection_data
{
	cvec_collision_2d_item_data collection;
};

//typedef cvec_collision_2d_item rodeo_collision_2d_collection_t;

typedef
void (*rodeo_collision_2d_resolver_f)(
	rodeo_collision_2d_item_data_t *a,
	rodeo_collision_2d_item_data_t *b
);

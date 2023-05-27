
// -- internal --
// public
#include "rodeo/collision_t.h"
#include "rodeo_types.h"

rodeo_collision_2d_world_t
rodeo_collision_2d_world_create(void);

void
rodeo_collision_2d_world_destroy(
	rodeo_collision_2d_world_t *world
);

cvec_collision_2d_world_item_value*
rodeo_collision_2d_world_item_create(
	rodeo_collision_2d_world_t *world,
	rodeo_collision_2d_world_item_t item_params
);

void
rodeo_collision_2d_world_item_destroy(
	cvec_collision_2d_world_item_value* cvec_value
);

void
rodeo_collision_2d_world_item_destroy_by_id(
    world_id id
);

rodeo_collision_2d_world_item_t*
rodeo_collision_2d_world_item_get_by_id(
    world_id id
);

void
rodeo_collision_2d_world_compare_self(
	rodeo_collision_2d_world_t *world,
	void (*resolve)(
		rodeo_collision_2d_world_item_t *a,
		rodeo_collision_2d_world_item_t *b
	)
);

void
rodeo_collision_2d_world_compare_other(
	rodeo_collision_2d_world_t *world_a,
	rodeo_collision_2d_world_t *world_b,
	void (*resolve)(
		rodeo_collision_2d_world_item_t *a,
		rodeo_collision_2d_world_item_t *b
	)
);

// from raylib GetCollisionRect
rodeo_rectangle_t
rodeo_collision_2d_get_collision_rect(
    rodeo_collision_2d_world_item_t *a,
    rodeo_collision_2d_world_item_t *b
);

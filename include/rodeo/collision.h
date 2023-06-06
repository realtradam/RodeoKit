
// -- internal --
// public
#include "rodeo/collision_t.h"
#include "rodeo_types.h"

rodeo_collision_2d_collection_t
rodeo_collision_2d_collection_create(intptr_t initial_capacity);

void
rodeo_collision_2d_collection_destroy(
	rodeo_collision_2d_collection_t collection
);

rodeo_collision_2d_item_t
rodeo_collision_2d_item_create(
	rodeo_collision_2d_collection_t collection,
	rodeo_collision_2d_item_data_t item_params
);

void
rodeo_collision_2d_item_destroy(
	rodeo_collision_2d_item_t item
);

void
rodeo_collision_2d_item_destroy_by_id(
    rodeo_collision_2d_item_id_t id
);

rodeo_collision_2d_item_t
rodeo_collision_2d_item_get_by_id(
    rodeo_collision_2d_item_id_t id
);

void
rodeo_collision_2d_collection_compare_self(
	rodeo_collision_2d_collection_t collection,
	rodeo_collision_2d_resolver_f resolver
);

void
rodeo_collision_2d_collection_compare_other(
	rodeo_collision_2d_collection_t collection_a,
	rodeo_collision_2d_collection_t collection_b,
	rodeo_collision_2d_resolver_f resolver
);

// from raylib GetCollisionRect
rodeo_rectangle_t
rodeo_collision_2d_get_collision_rect(
    rodeo_rectangle_t a,
    rodeo_rectangle_t b
);

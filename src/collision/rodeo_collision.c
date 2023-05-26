#include "rodeo/collision.h"
#include "rodeo/collision_t.h"
#include <stdio.h>

bool detect_collision(
	const rodeo_collision_2d_world_item_t *a,
	const rodeo_collision_2d_world_item_t *b
)
{
	return !(a->x+a->dx > b->x+b->dx + b->width ||
			b->x+b->dx > a->x+a->dx + a->width ||
			a->y+a->dy > b->y+b->dy + b->height ||
			b->y+b->dy > a->y+a->dy + a->height);
}

rodeo_collision_2d_world_t
rodeo_collision_2d_world_create(void)
{
	return cvec_collision_2d_world_item_init();
}

void
rodeo_collision_2d_world_destroy(
rodeo_collision_2d_world_t *world
)
{
	cvec_collision_2d_world_item_drop(world);
}

cvec_collision_2d_world_item_value*
rodeo_collision_2d_world_item_create(
	rodeo_collision_2d_world_t *world,
	rodeo_collision_2d_world_item_t item_params
)
{
	static uint32_t next_id = 0;
	item_params.id = next_id++;
	cvec_collision_2d_world_item_value* new_item = cvec_collision_2d_world_item_push(world, item_params);
	
	return new_item;
}

void
rodeo_collision_2d_world_item_destroy(
	rodeo_collision_2d_world_t *world,
	cvec_collision_2d_world_item_value* cvec_value
)
{
	cvec_collision_2d_world_item_value temp = *cvec_collision_2d_world_item_back(world);
	*cvec_collision_2d_world_item_back(world) = *cvec_value;
	*cvec_value = temp;
	cvec_collision_2d_world_item_pop(world);
}

rodeo_collision_2d_world_item_t*
rodeo_collision_2d_world_item_get_by_id(
	rodeo_collision_2d_world_t *world,
	uint32_t id
)
{
	c_foreach(i, cvec_collision_2d_world_item, *world) {
		if (i.ref->id == id) {
			return i.ref;
		}
	}
	return NULL;
}

void
rodeo_collision_2d_world_compare_self(
	rodeo_collision_2d_world_t *world,
	void (*resolve)(
		rodeo_collision_2d_world_item_t *a,
		rodeo_collision_2d_world_item_t *b
	)
)
{
	c_foreach(i, cvec_collision_2d_world_item, *world) {
		c_foreach(j, cvec_collision_2d_world_item, cvec_collision_2d_world_item_advance(i, 1), cvec_collision_2d_world_item_end(world)) {
			if (detect_collision(i.ref, j.ref)) {
				resolve(i.ref, j.ref);
			}
		}
	}
}

void
rodeo_collision_2d_world_compare_other(
	rodeo_collision_2d_world_t *world_a,
	rodeo_collision_2d_world_t *world_b,
	void (*resolve)(
		rodeo_collision_2d_world_item_t *a,
		rodeo_collision_2d_world_item_t *b
	)
)
{
	c_foreach(i, cvec_collision_2d_world_item, *world_a) {
		c_foreach(j, cvec_collision_2d_world_item, *world_b) {
			if (detect_collision(i.ref, j.ref)) {
				resolve(i.ref, j.ref);
			}
		}
	}
}


int rodeo_collision_2d_item_cmp(
	const rodeo_collision_2d_world_item_t* a,
	const rodeo_collision_2d_world_item_t* b
)
{
	if (a->id == b->id) {
		return 0;
	} else {
		return a->id > b->id ? 1 : -1;
	}
}

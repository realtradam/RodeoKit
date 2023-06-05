#include "rodeo/collision.h"
#include "rodeo/collision_t.h"
#include <stdio.h>

bool detect_collision(
	const rodeo_collision_2d_world_item_t a,
	const rodeo_collision_2d_world_item_t b
)
{
	return !(a.id.id == b.id.id ||
			a.rect.x+a.dx > b.rect.x+b.dx + b.rect.width ||
			b.rect.x+b.dx > a.rect.x+a.dx + a.rect.width ||
			a.rect.y+a.dy > b.rect.y+b.dy + b.rect.height ||
			b.rect.y+b.dy > a.rect.y+a.dy + a.rect.height);
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
	item_params.id.id = next_id++;
	item_params.id.world = world;
	cvec_collision_2d_world_item_value* new_item = cvec_collision_2d_world_item_push(world, item_params);
	
	return new_item;
}

void
rodeo_collision_2d_world_item_destroy(
	cvec_collision_2d_world_item_value* cvec_value
)
{
	if (cvec_value == NULL) { return; }
 	*cvec_value = *cvec_collision_2d_world_item_back(cvec_value->id.world);
    cvec_collision_2d_world_item_pop(cvec_value->id.world);
}

void
rodeo_collision_2d_world_item_destroy_by_id(
	world_id id
)
{
	rodeo_collision_2d_world_item_t* item = rodeo_collision_2d_world_item_get_by_id
	(id);
	rodeo_collision_2d_world_item_destroy(item);
} 

rodeo_collision_2d_world_item_t*
rodeo_collision_2d_world_item_get_by_id( 
	world_id id 
) 
{
	if(id.world == NULL)
	{
		return NULL;
	}
	c_foreach(i, cvec_collision_2d_world_item, *id.world) {
		if (i.ref->id.id == id.id) {
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
			if (detect_collision(*i.ref, *j.ref)) {
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
			if (detect_collision(*i.ref, *j.ref)) {
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
	if (a->id.id == b->id.id) {
		return 0;
	} else {
		return a->id.id > b->id.id ? 1 : -1;
	}
}

// from raylib GetCollisionRect
rodeo_rectangle_t
rodeo_collision_2d_get_collision_rect(
    rodeo_rectangle_t a,
    rodeo_rectangle_t b
)
{
	rodeo_rectangle_t overlap = { 0 };

    float left = (a.x > b.x)? a.x : b.x;
    float right_a = a.x + a.width;
    float right_b = b.x + b.width;
    float right = (right_a < right_b)? right_a : right_b;
    float top = (a.y > b.y)? a.y : b.y;
    float bottom_a = a.y + a.height;
    float bottom_b = b.y + b.height;
    float bottom = (bottom_a < bottom_b)? bottom_a : bottom_b;

    if ((left < right) && (top < bottom))
    {
        overlap.x = left;
        overlap.y = top;
        overlap.width = right - left;
        overlap.height = bottom - top;
    }

    return overlap;
}

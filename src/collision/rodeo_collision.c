
// -- internal --
// public
#include "rodeo/collision.h"
#include "rodeo/collision_t.h"
#include "rodeo/log.h"

// -- system --
#include <stdio.h>

bool irodeo_collision_2d_detect(
	const cvec_collision_2d_item_data_value a,
	const cvec_collision_2d_item_data_value b
) 
{
	return !(a.id.self_handle == b.id.self_handle ||
			a.rect.x+a.dx > b.rect.x+b.dx + b.rect.width ||
			b.rect.x+b.dx > a.rect.x+a.dx + a.rect.width ||
			a.rect.y+a.dy > b.rect.y+b.dy + b.rect.height ||
			b.rect.y+b.dy > a.rect.y+a.dy + a.rect.height);
}

rodeo_collision_2d_collection_t
rodeo_collision_2d_collection_create(intptr_t initial_capacity)
{
	rodeo_collision_2d_collection_t result = {0};
	result.data = calloc(1, sizeof(*result.data));
	cvec_collision_2d_item_data_reserve(&result.data->collection, initial_capacity);
	return result;
}

void
rodeo_collision_2d_collection_destroy(
rodeo_collision_2d_collection_t collection
)
{
	c_foreach(i, cvec_collision_2d_item_data, collection.data->collection) {
		free(i.ref->id.self_handle);
	}
	cvec_collision_2d_item_data_drop(&collection.data->collection);
	free(collection.data);
}

rodeo_collision_2d_item_t
rodeo_collision_2d_item_create(
	rodeo_collision_2d_collection_t collection,
	rodeo_collision_2d_item_data_t item_params
)
{
	bool rewrite_self_pointers = false;
	intptr_t capacity = cvec_collision_2d_item_data_capacity(&collection.data->collection);
	intptr_t size = cvec_collision_2d_item_data_size(&collection.data->collection);
	if(capacity >= size)
	{
		rewrite_self_pointers = true;
	}
	rodeo_collision_2d_item_t result = {0};
	result.data_handle = calloc(1, sizeof(result.data_handle));
	*result.data_handle = cvec_collision_2d_item_data_push(
		&collection.data->collection,
		item_params
	);
	(*result.data_handle)->id.collection = collection;
	(*result.data_handle)->id.self_handle = result.data_handle;

	if(rewrite_self_pointers)
	{
		c_foreach(i, cvec_collision_2d_item_data, collection.data->collection) {
			i.ref->id.collection.data = collection.data;
			(*i.ref->id.self_handle) = i.ref;
		}
	}
	
	return result;
}

void
rodeo_collision_2d_item_destroy(
	rodeo_collision_2d_item_t item
)
{
	if(item.data_handle == NULL || *item.data_handle == NULL)
	{
		rodeo_log(
			rodeo_logLevel_warning,
			"Attempted to destroy collision item that doesn't exist anymore"
		);
		if(item.data_handle != NULL)
		{
			free(item.data_handle);
		}
		return;
	}
	cvec_collision_2d_item_data *collection = &((*item.data_handle)->id.collection.data->collection);

	// set the back item to point to deletion item
	*cvec_collision_2d_item_data_back(collection)->id.self_handle = *item.data_handle;

	// copy back item into deletion item
	(**item.data_handle) = *cvec_collision_2d_item_data_back(collection);
	cvec_collision_2d_item_data_pop(collection);

	// free the handle
	free(item.data_handle);
}

void
rodeo_collision_2d_item_destroy_by_id(
	rodeo_collision_2d_item_id_t id
)
{
	rodeo_collision_2d_item_t item = rodeo_collision_2d_item_get_by_id(id);
	rodeo_collision_2d_item_destroy(item);
} 

rodeo_collision_2d_item_t
rodeo_collision_2d_item_get_by_id( 
	rodeo_collision_2d_item_id_t id 
) 
{
	if(id.collection.data == NULL)
	{
		rodeo_log(
			rodeo_logLevel_warning,
			"Attempted to find collision item that doesn't belong to a collection. It also may not exist at all"
		);
		return (rodeo_collision_2d_item_t){0};
	}
	else if(id.self_handle == NULL || *id.self_handle == NULL)
	{
		rodeo_log(
			rodeo_logLevel_warning,
			"Attempted to find collision item that doesn't exist anymore"
		);
		return (rodeo_collision_2d_item_t){0};
	}

	return (rodeo_collision_2d_item_t){.data_handle = id.self_handle};
}

void
rodeo_collision_2d_collection_compare_self(
	rodeo_collision_2d_collection_t collection,
	rodeo_collision_2d_resolver_f resolver
)
{
	c_foreach(i, cvec_collision_2d_item_data, collection.data->collection) {
		c_foreach(
			j,
			cvec_collision_2d_item_data,
			cvec_collision_2d_item_data_advance(i, 1),
			cvec_collision_2d_item_data_end(&collection.data->collection)
		)
		{
			if (irodeo_collision_2d_detect(*i.ref, *j.ref)) {
				resolver(i.ref, j.ref);
			}
		}
	}
}

void
rodeo_collision_2d_collection_compare_other(
	rodeo_collision_2d_collection_t collection_a,
	rodeo_collision_2d_collection_t collection_b,
	rodeo_collision_2d_resolver_f resolver
)
{
	c_foreach(i, cvec_collision_2d_item_data, collection_a.data->collection) {
		c_foreach(j, cvec_collision_2d_item_data, collection_b.data->collection) {
			if (irodeo_collision_2d_detect(*i.ref, *j.ref)) {
				resolver(i.ref, j.ref);
			}
		}
	}
}


int32_t irodeo_collision_2d_item_data_cmp(
	const rodeo_collision_2d_item_data_t* a,
	const rodeo_collision_2d_item_data_t* b
)
{
	if (a->id.self_handle == b->id.self_handle) {
		return 0;
	} else {
		return a->id.self_handle > b->id.self_handle ? 1 : -1;
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

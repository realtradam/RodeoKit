#pragma once

// -- internal --
// public
#include "rodeo/gfx_t.h"
#include "rodeo/math/vec2_t.h"
#include "rodeo/math/mat4_t.h"

// -- external --
#include "stc/cstr.h"

void
rodeo_gfx_init(float width, float height);

void
rodeo_gfx_deinit(void);

void
rodeo_gfx_frame_begin(void);

void
rodeo_gfx_frame_end(void);

float
rodeo_gfx_width_get(void);

float
rodeo_gfx_height_get(void);

rodeo_rectangle_t
rodeo_gfx_letterbox_first_get(void);

rodeo_rectangle_t
rodeo_gfx_letterbox_second_get(void);

cstr
rodeo_gfx_renderer_name_get(void);

void
rodeo_gfx_renderer_flush(void);

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_default_get(void);

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_create_from_RGBA8(
	const uint16_t width,
	const uint16_t height,
	const uint8_t memory[]
);

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_create_from_path(cstr path);

void
rodeo_gfx_texture_2d_destroy(rodeo_gfx_texture_2d_t texture);

void
rodeo_gfx_rectangle_draw(
	const rodeo_rectangle_t rectangle,
	const float turns,
	const rodeo_color_RGBAFloat_t color
);

void
rodeo_gfx_vertex_add(rodeo_gfx_vertex_t vertex);

uint16_t
rodeo_gfx_vertex_size(void);

uint16_t
rodeo_gfx_vertex_maxSize(void);

void
rodeo_gfx_index_add(rodeo_gfx_index_t index);

uint16_t
rodeo_gfx_index_size(void);

rodeo_gfx_index_t
rodeo_gfx_index_count_get(void);

void
rodeo_gfx_index_count_increment(uint16_t amount);

uint16_t
rodeo_gfx_index_maxSize(void);

void
rodeo_gfx_texture_set(rodeo_gfx_texture_2d_t texture);

void
rodeo_gfx_texture_2d_draw(
	const rodeo_rectangle_t destination,
	const rodeo_rectangle_t source,
	const float turns,
	const rodeo_math_vec2_t origin,
	const rodeo_color_RGBAFloat_t color,
	const rodeo_gfx_texture_2d_t texture
);

void
rodeo_gfx_renderer_flush(void);

uint32_t
rodeo_gfx_frame_limit_get(void);

cstr
rodeo_gfx_renderer_name_get(void);

uint64_t
rodeo_gfx_frame_count_get(void);

float
rodeo_gfx_frame_time_get(void);

float
rodeo_gfx_frame_perSecond_get(void);

void
rodeo_gfx_frame_limit_set(uint32_t limit);

uint32_t
rodeo_gfx_frame_limit_get(void);

void
rodeo_gfx_scissor_begin(rodeo_rectangle_t rectangle);

void
rodeo_gfx_scissor_end(void);

void
irodeo_gfx_matrix_init(void);

void
irodeo_gfx_matrix_deinit(void);

void
rodeo_gfx_matrix_set(rodeo_math_mat4_t matrix);

rodeo_math_mat4_t
rodeo_gfx_matrix_get(void);

void
rodeo_gfx_matrix_push(void);

void
rodeo_gfx_matrix_pop(void);

uint32_t
rodeo_gfx_matrix_size(void);

uint32_t
rodeo_gfx_matrix_capacity(void);

void
rodeo_gfx_camera_2d_begin(rodeo_gfx_camera_2d_t camera);

void
rodeo_gfx_camera_2d_end(void);

#define \
mrodeo_gfx_camera_do(camera) \
	mrodeo_defer_do( \
		rodeo_gfx_camera_2d_begin(camera), \
		rodeo_gfx_camera_2d_end() \
	)

#define \
mrodeo_gfx_scissor_do(rectangle) \
	mrodeo_defer_do( \
		rodeo_gfx_scissor_begin(rectangle), \
		rodeo_gfx_scissor_end() \
	)

#define									\
mrodeo_gfx_do(							\
	width,								\
	height								\
)										\
	mrodeo_defer_do(					\
		rodeo_gfx_init(width, height),	\
		rodeo_gfx_deinit()				\
	)


#define								\
mrodeo_gfx_frame_do(				\
)									\
	mrodeo_defer_do(				\
		rodeo_gfx_frame_begin(),	\
		rodeo_gfx_frame_end()		\
	)


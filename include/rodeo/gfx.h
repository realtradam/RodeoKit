#pragma once

// -- internal --
// public
#include "rodeo/gfx_t.h"

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
	const rodeo_color_RGBAFloat_t color
);

void
rodeo_gfx_texture_2d_draw(
	const rodeo_rectangle_t destination,
	const rodeo_rectangle_t source,
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


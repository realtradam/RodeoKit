
// -- internal --
// public
#include "rodeo.h"
// private
#include "rodeo_internal_types.h"

#define											\
mrodeo_bgfx_vertex_layout_do(vertex_layout)		\
	mrodeo_defer_do(							\
		bgfx_vertex_layout_begin(				\
			vertex_layout,						\
			bgfx_get_renderer_type()			\
		),										\
		bgfx_vertex_layout_end(vertex_layout)	\
	)

bgfx_shader_handle_t
irodeo_\
shader_load(const rodeo_string_t path);

void
irodeo_random_seed_set(stc64_t seed);

stc64_t*
irodeo_random_seed_get(void);

float
irodeo_frame_remaining_get(void);

void
irodeo_frame_stall(void);

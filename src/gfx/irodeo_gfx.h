
// -- internal --
// public
#include "rodeo/common.h"
// private
#include "gfx/irodeo_gfx_t.h"

// -- external --
#include "bgfx/c99/bgfx.h"
#include "stc/cstr.h"

bgfx_shader_handle_t
irodeo_gfx_shader_load(const cstr path);

void
irodeo_gfx_render_buffer_transient_alloc(void);

void
irodeo_gfx_frame_stall(void);

void
irodeo_gfx_dimensions_extra_update(void);

irodeo_gfx_dimensions_extra_t
irodeo_gfx_dimensions_extra_get(void);

#define											\
mrodeo_bgfx_vertex_layout_do(vertex_layout)		\
	mrodeo_defer_do(							\
		bgfx_vertex_layout_begin(				\
			vertex_layout,						\
			bgfx_get_renderer_type()			\
		),										\
		bgfx_vertex_layout_end(vertex_layout)	\
	)


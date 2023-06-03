#pragma once

// -- internal --
// public
#include "rodeo_config.h"
#include "rodeo_types.h"

// -- external --
#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
#endif
#include "SDL.h"
#include "SDL_syswm.h"
#include "bgfx/c99/bgfx.h"
#include "stc/crandom.h"
/*#define CGLM_FORCE_LEFT_HANDED*/
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
/*#define CGLM_CLIPSPACE_INCLUDE_ALL*/
#include "cglm/cglm.h"

typedef uint16_t irodeo_index_type_t;

typedef struct
{
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_SysWMinfo wmi;
	uint16_t screen_width;
	uint16_t screen_height;
	SDL_Event sdl_event;
	bool quit;

	bgfx_vertex_layout_t vertex_layout;
	//bgfx_dynamic_vertex_buffer_handle_t vertex_buffer_handle;
	//bgfx_dynamic_index_buffer_handle_t index_buffer_handle;
	bgfx_transient_vertex_buffer_t vertex_buffer_handle;
	bgfx_transient_index_buffer_t index_buffer_handle;
	rodeo_vertex_t *batched_vertices;
	irodeo_index_type_t *batched_indices;
	irodeo_index_type_t vertex_size;
	irodeo_index_type_t index_count;
	irodeo_index_type_t index_size;
	//irodeo_index_type_t batched_indices[(mrodeo_vertex_size_max / 4) * 6];
	rodeo_texture_2d_t default_texture;
	bgfx_texture_handle_t *active_texture_p;
	bgfx_shader_handle_t vertex_shader;
	bgfx_shader_handle_t fragment_shader;
	bgfx_program_handle_t program_shader;
	bgfx_uniform_handle_t texture_uniforms[2];
	mat4 view_matrix;
	mat4 proj_matrix;

	stc64_t random_seed;

	uint64_t frame_count;
	uint64_t start_frame;
	uint64_t end_frame;
	float frame_time;
	uint32_t frame_limit;
}
irodeo_state_t;

struct
irodeo_texture_internal_t
{
	bgfx_texture_handle_t texture_bgfx;
};

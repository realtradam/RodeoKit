#pragma once

// -- internal --
// public
#include "rodeo/gfx_t.h"
#include "rodeo/math.h"

// -- external --
#include "bgfx/c99/bgfx.h"

typedef uint16_t irodeo_index_type_t;

typedef
struct
{
	bgfx_vertex_layout_t vertex_layout;
	//bgfx_dynamic_vertex_buffer_handle_t vertex_buffer_handle;
	//bgfx_dynamic_index_buffer_handle_t index_buffer_handle;
	bgfx_transient_vertex_buffer_t vertex_buffer_handle;
	bgfx_transient_index_buffer_t index_buffer_handle;
	rodeo_gfx_vertex_t *batched_vertices;
	irodeo_index_type_t *batched_indices;
	irodeo_index_type_t vertex_size;
	irodeo_index_type_t index_count;
	irodeo_index_type_t index_size;
	//irodeo_index_type_t batched_indices[(mrodeo_vertex_size_max / 4) * 6];
	rodeo_gfx_texture_2d_t default_texture;
	bgfx_texture_handle_t *active_texture_p;
	bgfx_shader_handle_t vertex_shader;
	bgfx_shader_handle_t fragment_shader;
	bgfx_program_handle_t program_shader;
	bgfx_uniform_handle_t texture_uniforms[2];
	float target_width;
	float target_height;
	//mat4 view_matrix;
	//mat4 proj_matrix;
	rodeo_math_mat4_t view_matrix;
	rodeo_math_mat4_t proj_matrix;
	uint64_t frame_count;
	uint32_t frame_limit;
	uint32_t frame_start;
	uint32_t frame_end;
	float frame_time;
}
irodeo_gfx_state_t;

struct
irodeo_gfx_texture_2d
{
	bgfx_texture_handle_t texture_bgfx;
};


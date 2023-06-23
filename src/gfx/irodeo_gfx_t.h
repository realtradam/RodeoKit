#pragma once

// -- internal --
// public
#include "rodeo/gfx_t.h"
#include "rodeo/math_t.h"

// -- external --
#include "bgfx/c99/bgfx.h"

typedef
struct
{
	float target_width;
	float target_height;
	//	what the calculated size is to fit in the window
	float result_width;
	float result_height;
	float game_aspect;
	float window_aspect;
	float scale;
}
irodeo_gfx_dimensions_extra_t;

#define i_type stc_gfx_matrix_stack
#define i_val rodeo_math_mat4_t
#include <stc/cstack.h>

typedef
struct
{
	bgfx_vertex_layout_t vertex_layout;
	//bgfx_dynamic_vertex_buffer_handle_t vertex_buffer_handle;
	//bgfx_dynamic_index_buffer_handle_t index_buffer_handle;
	bgfx_transient_vertex_buffer_t vertex_buffer_handle;
	bgfx_transient_index_buffer_t index_buffer_handle;
	rodeo_gfx_vertex_t *batched_vertices;
	rodeo_gfx_index_t *batched_indices;
	rodeo_gfx_index_t vertex_size;
	rodeo_gfx_index_t index_count;
	rodeo_gfx_index_t index_size;
	//irodeo_gfx_index_t batched_indices[(mrodeo_vertex_size_max / 4) * 6];
	rodeo_gfx_texture_2d_t default_texture;
	bgfx_encoder_t *encoder;
	bgfx_texture_handle_t *active_texture;
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
	irodeo_gfx_dimensions_extra_t dimensions_extra;
	rodeo_math_mat4_t matrix_stack_top;
	stc_gfx_matrix_stack matrix_stack;
	rodeo_math_mat4_t camera_2d_matrix;
}
irodeo_gfx_state_t;

struct
irodeo_gfx_texture_2d
{
	bgfx_texture_handle_t texture_bgfx;
};


#pragma once

// -- internal --
// public
#include "rodeo_config.h"
#include "rodeo_types.h"

// -- system --
#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
#endif
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"

typedef struct
{
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_SysWMinfo wmi;
	int screen_width;
	int screen_height;
	SDL_Event sdl_event;
	bool quit;

	bgfx_vertex_layout_t vertex_layout;
	bgfx_dynamic_vertex_buffer_handle_t vertex_buffer_handle;
	bgfx_dynamic_index_buffer_handle_t index_buffer_handle;
	uint16_t vertex_size;
	rodeo_vertex_t batched_vertices[mrodeo_vertex_size_max];
	uint16_t index_count;
	uint16_t index_size;
	uint16_t batched_indices[(mrodeo_vertex_size_max / 4) * 6];
	uint16_t active_texture_id;
	bgfx_shader_handle_t vertex_shader;
	bgfx_shader_handle_t fragment_shader;
	bgfx_program_handle_t program_shader;

	uint64_t frame_count;
	uint64_t start_frame;
	uint64_t end_frame;
	float frame_time;
	uint32_t frame_limit;
}
irodeo_state_t;

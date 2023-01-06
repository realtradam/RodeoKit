#pragma once
#include <stdbool.h>
#include <stdint.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"

#define RODEO__MAX_VERTEX_SIZE 8192

typedef
struct
Rodeo__\
color_rgba_t
{
	float red;
	float green;
	float blue;
	float alpha;
} Rodeo__color_t;

typedef
struct
Rodeo__\
position_color_vertex_t
{
	float x;
	float y;
	float z;
	uint32_t abgr;
} Rodeo__position_color_vertex_t;

typedef
struct
Rodeo__\
data_t
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
	Rodeo__position_color_vertex_t batched_vertices[RODEO__MAX_VERTEX_SIZE];
	uint16_t index_count;
	uint16_t index_size;
	uint16_t batched_indices[(RODEO__MAX_VERTEX_SIZE / 4) * 6];
	bgfx_shader_handle_t vertex_shader;
	bgfx_shader_handle_t fragment_shader;
	bgfx_program_handle_t program_shader;
} Rodeo__data_t;

// -- internal --
// public
#include "rodeo.h" // TODO remove this
#include "rodeo/gfx.h"
#include "rodeo/window.h"
#include "rodeo/log.h"
#include "rodeo/math.h"
// private
#include "gfx/irodeo_gfx.h"
#include "window/irodeo_window.h"
#include "rodeo_config.h"

// -- external --
#include "bgfx/c99/bgfx.h"
#include "SDL_image.h"
#include "SDL.h" // used for timing, need to replace in this file with BGFX at some point

// -- system --
#include <math.h>

static irodeo_gfx_state_t irodeo_gfx_state = {0};

void
rodeo_gfx_init(float width, float height)
{
#ifdef __EMSCRIPTEN__
	bgfx_render_frame(-1);
#endif
	irodeo_gfx_state.target_width = width;
	irodeo_gfx_state.target_height = height;
	irodeo_gfx_dimensions_extra_update();

	bgfx_platform_data_t pd = {0};
	memset(&pd, 0, sizeof(bgfx_platform_data_t));

#if !__EMSCRIPTEN__
	// x11
	pd.ndt = irodeo_window_wmi_get().info.x11.display;
	pd.nwh = (void*)(uintptr_t)irodeo_window_wmi_get().info.x11.window;
#else
	// web
	pd.nwh = (void*)"#canvas";
#endif

	bgfx_init_t init = {0};
	bgfx_init_ctor(&init);
	//init.type = BGFX_RENDERER_TYPE_COUNT; // auto determine renderer
	init.type = BGFX_RENDERER_TYPE_OPENGL; // force opengl renderer
										   //SDL_GetWindowSize(irodeo_gfx_state.window, &irodeo_gfx_state.screen_width, &irodeo_gfx_state.screen_height);
	init.resolution.width = rodeo_window_height_get();
	init.resolution.height = rodeo_window_width_get();
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.platformData = pd;
	bgfx_init(&init);

	bgfx_set_debug(BGFX_DEBUG_TEXT);

	//bgfx_set_state(BGFX_STATE_CULL_CCW, 0);

	bgfx_dbg_text_clear(0x0, false);

	bgfx_set_view_clear(
			0,
			BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
			//0x443355FF,
			0x000000FF,
			1.0f,
			0
			);

	rodeo_log(rodeo_logLevel_info, "Setting up default render pipeline...");
	// set up vertex layout
	mrodeo_bgfx_vertex_layout_do(&irodeo_gfx_state.vertex_layout)
	{
		bgfx_vertex_layout_add(&irodeo_gfx_state.vertex_layout, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&irodeo_gfx_state.vertex_layout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&irodeo_gfx_state.vertex_layout, BGFX_ATTRIB_TEXCOORD0, 2, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&irodeo_gfx_state.vertex_layout, BGFX_ATTRIB_TEXCOORD1, 1, BGFX_ATTRIB_TYPE_FLOAT, false, false);
	}

	// load shaders
	cstr shader_path = cstr_lit("???");
	switch(bgfx_get_renderer_type()) {
		case BGFX_RENDERER_TYPE_NOOP:
			rodeo_log(
					rodeo_logLevel_error,
					"BGFX failed to get determine an appropriate renderer"
					);
			exit(EXIT_FAILURE);
		case BGFX_RENDERER_TYPE_OPENGLES:
			cstr_assign(
					&shader_path,
					"shaders/100_es/"
					);
			break;
		case BGFX_RENDERER_TYPE_VULKAN:
			cstr_assign(
					&shader_path,
					"shaders/spirv/"
					);
			break;
		case BGFX_RENDERER_TYPE_OPENGL:
			cstr_assign(
					&shader_path,
					"shaders/opengl/"
					);
			break;
		default:
			rodeo_log(
					rodeo_logLevel_error,
					"No shaders implemented for BGFX renderer chosen"
					);
			exit(EXIT_FAILURE);
	}
	cstr vertex_shader_path = cstr_lit("simple.vertex.bin");
	cstr fragment_shader_path = cstr_lit("simple.fragment.bin");

	cstr_insert_s(
			&vertex_shader_path,
			0,
			shader_path
			);
	cstr_insert_s(
			&fragment_shader_path,
			0,
			shader_path
			);

	irodeo_gfx_state.vertex_shader = irodeo_gfx_shader_load(vertex_shader_path);
	irodeo_gfx_state.fragment_shader = irodeo_gfx_shader_load(fragment_shader_path);
	irodeo_gfx_state.program_shader = bgfx_create_program(
			irodeo_gfx_state.vertex_shader,
			irodeo_gfx_state.fragment_shader,
			true
			);
	rodeo_log(
			rodeo_logLevel_info,
			"Default render pipeline finished setup"
			);

	//bgfx_texture_handle_t default_bgfx_texture = rodeo_texture_2d_create_default();

	irodeo_gfx_state.default_texture.data = malloc(sizeof(*irodeo_gfx_state.default_texture.data));

	// used for binding textures to shader uniforms
	irodeo_gfx_state.texture_uniforms[0] = bgfx_create_uniform("default_texture", BGFX_UNIFORM_TYPE_SAMPLER, 1);
	irodeo_gfx_state.texture_uniforms[1] = bgfx_create_uniform("texture_0", BGFX_UNIFORM_TYPE_SAMPLER, 1);

	{
		// represents 1 pixel sized white texture
		const uint8_t default_texture_data[] = {
			//red, blue, green, alpha
			0xff, 0xff, 0xff, 0xff,
		};

		irodeo_gfx_state.default_texture.data->texture_bgfx = 
			bgfx_create_texture_2d(
					1,
					1,
					false,
					0,
					BGFX_TEXTURE_FORMAT_RGBA8,
					BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_MAG_POINT,
					bgfx_copy(
						&default_texture_data,
						sizeof(default_texture_data)
						)
					);
		irodeo_gfx_state.default_texture.width = 1;
		irodeo_gfx_state.default_texture.height = 1;

		irodeo_gfx_state.active_texture = &irodeo_gfx_state.default_texture.data->texture_bgfx;
	}

	SDL_SetWindowResizable(irodeo_window_get(), true);

	bgfx_reset(
			(uint32_t)rodeo_window_width_get(),
			(uint32_t)rodeo_window_height_get(),
			//BGFX_RESET_MSAA_X16 | BGFX_RESET_MAXANISOTROPY,
			BGFX_RESET_VSYNC,
			BGFX_TEXTURE_FORMAT_COUNT
			);

	irodeo_gfx_matrix_init();
	irodeo_gfx_camera_2d_init();

	irodeo_gfx_state.frame_end = (uint32_t)SDL_GetPerformanceCounter();
}

void
rodeo_gfx_deinit(void)
{
	irodeo_gfx_camera_2d_deinit();
	irodeo_gfx_matrix_deinit();

	free(irodeo_gfx_state.default_texture.data);

	bgfx_destroy_program(irodeo_gfx_state.program_shader);
	bgfx_shutdown();
}

void
rodeo_gfx_frame_begin(void)
{
	irodeo_gfx_dimensions_extra_t dm = irodeo_gfx_dimensions_extra_get();

	// get identity
	irodeo_gfx_state.view_matrix = rodeo_math_mat4_identity();
	irodeo_gfx_state.proj_matrix = rodeo_math_mat4_identity();

	// calculate orthographic
	rodeo_math_mat4_t ortho = rodeo_math_mat4_orthographic(
		0,
		dm.result_width,
		dm.result_height,
		0,
		-100.0f,
		100.0f
	);

	// calculate translation
	rodeo_math_vec3_t offset = {
		.val.x = 1 - (1 * (dm.target_width / dm.result_width)), // x
		.val.y = -(1 - (1 * (dm.target_height / dm.result_height))), // y
		.val.z = 0
	};

	// apply translation * orthographic
	irodeo_gfx_state.proj_matrix = rodeo_math_mat4_translate(irodeo_gfx_state.proj_matrix, offset);
	irodeo_gfx_state.proj_matrix = rodeo_math_mat4_multiply(irodeo_gfx_state.proj_matrix, ortho);

	// push the result to bgfx
	bgfx_set_view_transform(0, irodeo_gfx_state.view_matrix.raw, irodeo_gfx_state.proj_matrix.raw);
	bgfx_set_view_rect(0, 0, 0, (uint16_t)rodeo_window_width_get(), (uint16_t)rodeo_window_height_get());

	irodeo_gfx_render_buffer_transient_alloc();
	bgfx_touch(0);

	irodeo_gfx_state.frame_start = irodeo_gfx_state.frame_end;
}

void
rodeo_gfx_frame_end(void)
{
	rodeo_gfx_renderer_flush();

	bgfx_frame(false);

#ifndef __EMSCRIPTEN__
	irodeo_gfx_frame_stall();
#endif
	irodeo_gfx_state.frame_count += 1;
	irodeo_gfx_state.frame_end = (uint32_t)SDL_GetPerformanceCounter();
	//
#ifndef __EMSCRIPTEN__
	//irodeo_gfx_state.frame_time = ((float)(irodeo_gfx_state.frame_end - irodeo_gfx_state.frame_start) * 1000.0f / (float)SDL_GetPerformanceFrequency());
	irodeo_gfx_state.frame_time = (1.0f/60.f) * 1000; //((float)(state.end_frame - state.start_frame) * 1000.0f / (float)SDL_GetPerformanceFrequency());
#else
	irodeo_gfx_state.frame_time = (1.0f/60.f) * 1000; //((float)(state.end_frame - state.start_frame) * 1000.0f / (float)SDL_GetPerformanceFrequency());
#endif
}

float
rodeo_gfx_width_get(void)
{
	return irodeo_gfx_state.target_width;
}

float
rodeo_gfx_height_get(void)
{
	return irodeo_gfx_state.target_height;
}

void
irodeo_gfx_dimensions_extra_update(void)
{
	// scale the game screen to fit window size with letterbox
	//	what size we declare the game screen to be within
	const float target_width = rodeo_gfx_width_get();
	const float target_height = rodeo_gfx_height_get();
	//	what the calculated size is to fit in the window
	float result_width = target_width;
	float result_height = target_height;
	const float game_aspect = target_width / target_height;
	const float window_aspect = (float)rodeo_window_width_get()/(float)rodeo_window_height_get();
	float scale = 1.0f;
	if(window_aspect > game_aspect)
	{
		result_width /= (game_aspect) / window_aspect;
		scale = (float)rodeo_window_height_get() / target_height;
	}
	else if(window_aspect < game_aspect)
	{
		result_height *= (game_aspect) / window_aspect;
		scale = (float)rodeo_window_width_get() / target_width;
	}
	irodeo_gfx_dimensions_extra_t result = {
		.target_width = target_width,
		.target_height = target_height,
		.result_width = result_width,
		.result_height = result_height,
		.game_aspect = game_aspect,
		.window_aspect = window_aspect,
		.scale = scale
	};
	irodeo_gfx_state.dimensions_extra = result;
}

irodeo_gfx_dimensions_extra_t
irodeo_gfx_dimensions_extra_get(void)
{
	return irodeo_gfx_state.dimensions_extra;
}

rodeo_rectangle_t
rodeo_gfx_letterbox_first_get(void)
{
	irodeo_gfx_dimensions_extra_t dm = irodeo_gfx_dimensions_extra_get();

	rodeo_rectangle_t result = {0};

	// while checking for float equality should generally never be done
	// in this case it is ok because the case where they are exactly equal
	// causes the letterboxes to fill the screen instead of not existing.
	// this is avoided this by leaving the rectangle size at 0 in that case.
	if(dm.window_aspect != dm.game_aspect)
	{
		result = (rodeo_rectangle_t){
			.x = (-dm.result_width + dm.target_width) / 2,
				.y = (-dm.result_height + dm.target_height) / 2,
				.width = (dm.result_width * ((dm.window_aspect > dm.game_aspect) ? 0 : 1 )) + ((dm.result_width - dm.target_width) / 2),
				.height = (dm.result_height * ((dm.window_aspect < dm.game_aspect) ? 0 : 1 )) + ((dm.result_height - dm.target_height) / 2),
		};
	}

	return result;
}

rodeo_rectangle_t
rodeo_gfx_letterbox_second_get(void)
{
rodeo_rectangle_t result = rodeo_gfx_letterbox_first_get();
	if(rodeo_gfx_width_get() != result.width)
	{ // second box needs to be offset to the right
		result.x += rodeo_gfx_width_get() + result.width;
	}
	else
	{ // second box needs to be offset downward
		result.y += rodeo_gfx_height_get() + result.height;
	}
	return result;
}

float
rodeo_gfx_frame_time_get(void)
{
	return irodeo_gfx_state.frame_time; //(float)bgfx_get_stats()->cpuTimeFrame;
}

float
rodeo_gfx_frame_perSecond_get(void)
{
	return 1.0f / (rodeo_gfx_frame_time_get() / 1000.0f);
}

// measures how much time there is left in the remaining frame until
// the frame target time is reached. If we surpassed the target time
// then this will be negative
float
irodeo_gfx_frame_remaining_get(void)
{
#ifdef __EMSCRIPTEN__
	float target = 60.0f;
#else
	float target = (float)rodeo_gfx_frame_limit_get();
#endif

	float result = (1/target * 1000.0f) - ((float)(SDL_GetPerformanceCounter() - irodeo_gfx_state.frame_start) / (float)SDL_GetPerformanceFrequency() * 1000.0f);

	return result;
}


// used internally at the end of every frame to fill for time
// in order to reach the desired framerate
void
irodeo_gfx_frame_stall(void)
{
	// if no frame limit then run as fast as possible
	if(rodeo_gfx_frame_limit_get() == 0)
	{
		return;
	}

	// sleep isnt perfectly accurate so we sleep for a slightly shorter
	// amount of time
	float stall_time = irodeo_gfx_frame_remaining_get();
	if(stall_time > 0.0005)
	{
		SDL_Delay((uint32_t)(stall_time * 0.9995));
	}

	// then we spinlock for the small remaining amount of time
	stall_time = irodeo_gfx_frame_remaining_get();
	while(stall_time > 0.0005) {
		stall_time = irodeo_gfx_frame_remaining_get();
	}
}

#include "math/irodeo_mat4.h"

void
rodeo_gfx_renderer_flush(void)
{
	// set default texture
	bgfx_set_texture(
			0,
			irodeo_gfx_state.texture_uniforms[0],
			rodeo_gfx_texture_2d_default_get().data->texture_bgfx,
			UINT32_MAX
			);
	if(irodeo_gfx_state.active_texture != NULL)
	{
		// set dynamic texture
		bgfx_set_texture(
				1,
				irodeo_gfx_state.texture_uniforms[1],
				*irodeo_gfx_state.active_texture,
				UINT32_MAX
				);
	}
	else
	{
		// set to default if none exists
		bgfx_set_texture(
				1,
				irodeo_gfx_state.texture_uniforms[1],
				rodeo_gfx_texture_2d_default_get().data->texture_bgfx,
				UINT32_MAX
				);
	}

	if(irodeo_gfx_state.vertex_size > 0)
	{
		bgfx_set_state(
				BGFX_STATE_CULL_CW |
				BGFX_STATE_WRITE_RGB |
				BGFX_STATE_WRITE_A |
				//BGFX_STATE_DEPTH_TEST_LESS |
				//BGFX_STATE_MSAA |
				BGFX_STATE_BLEND_ALPHA,
				0
				);

		// upload remaining batched vertices
		bgfx_set_transient_vertex_buffer(0, &irodeo_gfx_state.vertex_buffer_handle, 0, irodeo_gfx_state.vertex_size);
		//const bgfx_memory_t* vbm = bgfx_copy(irodeo_gfx_state.batched_vertices, sizeof(rodeo_gfx_vertex_t) * irodeo_gfx_state.vertex_size);
		//bgfx_update_dynamic_vertex_buffer(irodeo_gfx_state.vertex_buffer_handle,  0, vbm);

		// upload remaining batched indices
		bgfx_set_transient_index_buffer(&irodeo_gfx_state.index_buffer_handle, 0, irodeo_gfx_state.index_size);
		//bgfx_set_dynamic_index_buffer(irodeo_gfx_state.index_buffer_handle, 0, irodeo_gfx_state.index_size);
		//const bgfx_memory_t* ibm = bgfx_copy(irodeo_gfx_state.batched_indices, sizeof(uint16_t) * irodeo_gfx_state.index_size);
		//bgfx_update_dynamic_index_buffer(irodeo_gfx_state.index_buffer_handle, 0, ibm);
		
		// apply matrices
		//rodeo_math_mat4_t result_matrix = rodeo_math_mat4_multiply(
		//	irodeo_gfx_state.proj_matrix,
		//	irodeo_gfx_state.matrix_stack_top
		//);
		//bgfx_set_transform(&result_matrix.raw, 1);
	
		//irodeo_print_matrix(irodeo_gfx_state.camera_2d_matrix);
		rodeo_math_mat4_t transform = rodeo_math_mat4_multiply(
			irodeo_gfx_state.matrix_stack_top,
			irodeo_gfx_state.camera_2d_matrix
		);
		bgfx_set_transform(&transform, 1);

		// submit vertices & batches
		bgfx_submit(0, irodeo_gfx_state.program_shader, 0, BGFX_DISCARD_NONE);

		// reset arrays
		irodeo_gfx_state.vertex_size = 0;
		irodeo_gfx_state.index_size = 0;
		irodeo_gfx_state.index_count = 0;

		// allocate new buffers
		irodeo_gfx_render_buffer_transient_alloc();
	}
	irodeo_gfx_state.active_texture = NULL;
}

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_default_get(void)
{
	return irodeo_gfx_state.default_texture;
}

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_create_from_RGBA8(
		const uint16_t width,
		const uint16_t height,
		const uint8_t memory[]
		)
{
	rodeo_gfx_texture_2d_t texture;
	texture.data = malloc(sizeof(*texture.data));
	bgfx_copy(memory, (uint32_t)width * (uint32_t)height * sizeof(uint8_t) * 4);
	texture.data->texture_bgfx =
		bgfx_create_texture_2d(
				width,
				height,
				false,
				0,
				BGFX_TEXTURE_FORMAT_RGBA8,
				BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_MAG_POINT,
				bgfx_copy(memory, (uint32_t)width * (uint32_t)height * sizeof(uint8_t) * 4)
				);

	texture.width = width;
	texture.height = height;

	return texture;
}

void
rodeo_gfx_texture_2d_destroy(rodeo_gfx_texture_2d_t texture)
{
	bgfx_destroy_texture(texture.data->texture_bgfx);
	free(texture.data);
}

void
rodeo_gfx_rectangle_draw(
	const rodeo_rectangle_t rectangle,
	const float turns,
	const rodeo_color_RGBAFloat_t color
)
{
	rodeo_gfx_texture_2d_draw(
			rectangle,
			(rodeo_rectangle_t){ 0, 0, (float)rodeo_gfx_texture_2d_default_get().width, (float)rodeo_gfx_texture_2d_default_get().height },
			turns,
			(rodeo_math_vec2_t){0},
			color,
			rodeo_gfx_texture_2d_default_get()
			);
}

void
rodeo_gfx_vertex_add(rodeo_gfx_vertex_t vertex)
{
	if(irodeo_gfx_state.vertex_size >= mrodeo_vertex_size_max)
	{
		rodeo_gfx_renderer_flush();
	}
	irodeo_gfx_state.batched_vertices[irodeo_gfx_state.vertex_size] = vertex;
	irodeo_gfx_state.vertex_size += 1;
}

uint16_t
rodeo_gfx_vertex_size(void)
{
	return irodeo_gfx_state.vertex_size;
}

uint16_t
rodeo_gfx_vertex_maxSize(void)
{
	return mrodeo_vertex_size_max;
}

void
rodeo_gfx_index_add(rodeo_gfx_index_t index)
{
	if(irodeo_gfx_state.index_size >= mrodeo_index_size_max)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Exceeding the max number of indices for this draw call, index discarded"
		);
	}
	else
	{
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = index;
		irodeo_gfx_state.index_size += 1;
	}
}

uint16_t
rodeo_gfx_index_size(void)
{
	return irodeo_gfx_state.index_size;
}

rodeo_gfx_index_t
rodeo_gfx_index_count_get(void)
{
	return irodeo_gfx_state.index_count;
}

void
rodeo_gfx_index_count_increment(uint16_t amount)
{
	irodeo_gfx_state.index_count += amount;
}

uint16_t
rodeo_gfx_index_maxSize(void)
{
	return mrodeo_index_size_max;
}

void
rodeo_gfx_texture_set(rodeo_gfx_texture_2d_t texture)
{

	if(&texture.data->texture_bgfx != irodeo_gfx_state.active_texture)
	{
		if(irodeo_gfx_state.active_texture != NULL)
		{
			rodeo_gfx_renderer_flush();
		}
		irodeo_gfx_state.active_texture = &texture.data->texture_bgfx;
	}
}

void
rodeo_gfx_texture_2d_draw(
	const rodeo_rectangle_t destination,
	const rodeo_rectangle_t source,
	const float turns,
	const rodeo_math_vec2_t origin,
	const rodeo_color_RGBAFloat_t color,
	const rodeo_gfx_texture_2d_t texture
)
{
	// whether to use default or custom texture
	float texture_uniform_slot = 0.0;

	rodeo_rectangle_t source_applied;
	if((source.height != 0 || source.width != 0) && texture.data != NULL)
	{
		source_applied = (rodeo_rectangle_t){
			.x = source.x / (float)texture.width,
			.y = source.y / (float)texture.height,
			.width = source.width / (float)texture.width,
			.height = source.height / (float)texture.height,
		};
	}
	else
	{
		source_applied = (rodeo_rectangle_t){
			.x = 0.0f,
			.y = 0.0f,
			.width = 1.0f,
			.height = 1.0f,
		};
	}

	if(texture.data != NULL)
	{
		rodeo_gfx_texture_set(texture);
		texture_uniform_slot = 1.0;
	}


	if(irodeo_gfx_state.vertex_size + 4 > mrodeo_vertex_size_max)
	{
		rodeo_gfx_renderer_flush();
	}

	//rodeo_math_vec2_t origin = {0};
	rodeo_math_vec2_t vertex_pos[4] = {
		{
			.val.x = destination.x,
			.val.y = destination.y
		},
		{
			.val.x = destination.x,
			.val.y = destination.y
		},
		{
			.val.x = destination.x,
			.val.y = destination.y
		},
		{
			.val.x = destination.x,
			.val.y = destination.y
		}
	};

	if(turns == 0.0f)
	{
		vertex_pos[0].val.x += destination.width - origin.val.x;
		vertex_pos[0].val.y += destination.height - origin.val.y;

		vertex_pos[1].val.x += destination.width - origin.val.x;
		vertex_pos[1].val.y += -origin.val.y;

		vertex_pos[2].val.x += -origin.val.x;
		vertex_pos[2].val.y += -origin.val.y;

		vertex_pos[3].val.x += -origin.val.x;
		vertex_pos[3].val.y += destination.height - origin.val.y;
	}
	else
	{
		float sin_rotation = sinf(rodeo_math_turns_to_radians(turns));
		float cos_rotation = cosf(rodeo_math_turns_to_radians(turns));

		// bottom right
		vertex_pos[0].val.x += (destination.width - origin.val.x) * cos_rotation - (destination.height -origin.val.y) * sin_rotation;
		vertex_pos[0].val.y += (destination.width - origin.val.x) * sin_rotation + (destination.height - origin.val.y) * cos_rotation;

		// top right
		vertex_pos[1].val.x += (destination.width - origin.val.x) * cos_rotation - -origin.val.y * sin_rotation;
		vertex_pos[1].val.y += (destination.width - origin.val.x) * sin_rotation + -origin.val.y * cos_rotation;

		// top left
		vertex_pos[2].val.x += -origin.val.x * cos_rotation - -origin.val.y * sin_rotation;
		vertex_pos[2].val.y += -origin.val.x * sin_rotation + -origin.val.y * cos_rotation;

		// bottom left
		vertex_pos[3].val.x += -origin.val.x * cos_rotation - (destination.height - origin.val.y) * sin_rotation;
		vertex_pos[3].val.y += -origin.val.y * sin_rotation + (destination.height - origin.val.y) * cos_rotation;

		/*
		vertex_pos[0] = (rodeo_math_vec2_t){
			.val.x = -(destination.height * sin_rotation) + (destination.width * cos_rotation) + destination.x,
			.val.y = (destination.height * cos_rotation) + (destination.width * sin_rotation) + destination.y
		};
		vertex_pos[1] = (rodeo_math_vec2_t){
			.val.x = -(destination.width * cos_rotation) + destination.x,
			.val.y = (destination.width * sin_rotation) + destination.y
		};
		vertex_pos[2] = (rodeo_math_vec2_t){
			.val.x = destination.x,
			.val.y = destination.y
		};
		vertex_pos[3] = (rodeo_math_vec2_t){
			.val.x = -(destination.height * sin_rotation) + destination.x,
			.val.y = (destination.height * cos_rotation) + destination.y
		};
		*/
	}

	rodeo_gfx_vertex_add(
		(rodeo_gfx_vertex_t)
		{ 
			.x = vertex_pos[0].val.x,
			.y = vertex_pos[0].val.y,
			//.z = 0.0f, 
			.color = color,
			.texture_id = texture_uniform_slot,
			.texture_x = source_applied.width + source_applied.x,
			.texture_y = source_applied.height + source_applied.y,
		}
	);
	rodeo_gfx_vertex_add(
		(rodeo_gfx_vertex_t)
		{ 
			.x = vertex_pos[1].val.x,
			.y = vertex_pos[1].val.y,
			//.z = 0.0f, 
			.color = color,
			.texture_id = texture_uniform_slot,
			.texture_x = source_applied.width + source_applied.x,
			.texture_y = source_applied.y,
		}
	);
	rodeo_gfx_vertex_add(
		(rodeo_gfx_vertex_t)
		{ 
			.x = vertex_pos[2].val.x,
			.y = vertex_pos[2].val.y,
			//.z = 0.0f, 
			.color = color,
			.texture_id = texture_uniform_slot,
			.texture_x = source_applied.x,
			.texture_y = source_applied.y,
		}
	);
	rodeo_gfx_vertex_add(
		(rodeo_gfx_vertex_t)
		{ 
			.x = vertex_pos[3].val.x,
			.y = vertex_pos[3].val.y,
			//.z = 0.0f, 
			.color = color,
			.texture_id = texture_uniform_slot,
			.texture_x = source_applied.x,
			.texture_y = source_applied.height + source_applied.y,
		}
	);

	rodeo_gfx_index_t indices[] =
	{
		0, 1, 3,
		1, 2, 3
			//2, 1, 0,
			//2, 3, 1
	};
	for(int8_t i = 0; i < (uint8_t)(sizeof(indices) / sizeof(indices[0])); ++i)
	{
		rodeo_gfx_index_add(indices[i] + rodeo_gfx_index_count_get());
	}
	rodeo_gfx_index_count_increment(4);
}

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_create_from_path(cstr path)
{
	// load image to surface
	SDL_Surface *surface = IMG_Load(cstr_str(&path));
	if(surface == NULL)
	{
		rodeo_log(
				rodeo_logLevel_error,
				"Loading texture from image failed: %s",
				IMG_GetError()
				);
		return (rodeo_gfx_texture_2d_t){0};
	}

	// check and handle a color key for transparency
	// not sure if I actually need this...
	//uint32_t color_key;
	//if(SDL_GetColorKey(surface, &color_key) == 0)
	//{
	//	SDL_SetColorKey(surface, SDL_TRUE, color_key);
	//}

	// convert pixel format of surface into RGBA8
	SDL_Surface *converted_surface =
		SDL_ConvertSurfaceFormat(
				surface,
				// pixel format needs to be backwards
				// of what bgfx uses for some reason
				SDL_PIXELFORMAT_ABGR8888,
				0
				);
	if(converted_surface == NULL)
	{
		rodeo_log(
				rodeo_logLevel_error,
				"Converting image to RGBA8 while loading texture failed: %s",
				SDL_GetError()
				);
		SDL_FreeSurface(surface);
		return (rodeo_gfx_texture_2d_t){0};
	}

	// load the pixel data into our own texture
	rodeo_gfx_texture_2d_t texture = rodeo_gfx_texture_2d_create_from_RGBA8(
			(uint16_t)converted_surface->w,
			(uint16_t)converted_surface->h,
			converted_surface->pixels
			);

	SDL_FreeSurface(surface);
	SDL_FreeSurface(converted_surface);

	return texture;
}

uint64_t
rodeo_gfx_frame_count_get(void)
{
	return irodeo_gfx_state.frame_count;
}

void
rodeo_gfx_frame_limit_set(uint32_t limit)
{
#ifdef __EMSCRIPTEN__
	rodeo_log(
			rodeo_logLevel_warning,
			"Framerate limit cannot be set on web platform. Limit is enforced by platform to 60fps"
			);
#else
	irodeo_gfx_state.frame_limit = limit;
#endif
}

uint32_t
rodeo_gfx_frame_limit_get(void)
{
#ifdef __EMSCRIPTEN__
	return 60;
#else
	return irodeo_gfx_state.frame_limit;
#endif
}

cstr
rodeo_gfx_renderer_name_get(void)
{
	return cstr_from(
		bgfx_get_renderer_name(bgfx_get_renderer_type())
	);
}

void
rodeo_gfx_scissor_begin(rodeo_rectangle_t rectangle)
{
	rodeo_gfx_renderer_flush();

	irodeo_gfx_dimensions_extra_t dm = irodeo_gfx_dimensions_extra_get();

	rectangle.x *= dm.scale;
	rectangle.y *= dm.scale;
	rectangle.width *= dm.scale;
	rectangle.height *= dm.scale;

	if(dm.window_aspect > dm.game_aspect)
	{
		rectangle.x += rodeo_gfx_letterbox_first_get().width * dm.scale;
	}
	else if(dm.window_aspect < dm.game_aspect)
	{
		rectangle.y += rodeo_gfx_letterbox_first_get().height * dm.scale;
	}

	// BGFX only accepts unsigned so it will break if the x/y values are outside the top
	// or left boundaries
	if(rectangle.x < 0)
	{
		rectangle.width += rectangle.x;
		rectangle.x = 0;
	}
	if(rectangle.y < 0)
	{
		rectangle.height += rectangle.y;
		rectangle.y = 0;
	}

	bgfx_set_scissor((uint16_t)roundf(rectangle.x), (uint16_t)roundf(rectangle.y), (uint16_t)roundf(rectangle.width), (uint16_t)roundf(rectangle.height));
}

void
rodeo_gfx_scissor_end(void)
{
	rodeo_gfx_renderer_flush();
	bgfx_set_scissor_cached(UINT16_MAX);
}

// matrix design: by default start with first one being identity and pushed
// popping past the first one resets it to idenity

void
irodeo_gfx_matrix_init(void)
{
	irodeo_gfx_state.matrix_stack = stc_gfx_matrix_stack_with_capacity(32);
	irodeo_gfx_state.matrix_stack_top = rodeo_math_mat4_identity();
	stc_gfx_matrix_stack_push(&irodeo_gfx_state.matrix_stack, rodeo_gfx_matrix_get());

}

void
irodeo_gfx_matrix_deinit(void)
{
	stc_gfx_matrix_stack_drop(&irodeo_gfx_state.matrix_stack);
}

void
rodeo_gfx_matrix_set(rodeo_math_mat4_t matrix)
{
	rodeo_gfx_renderer_flush();
	//*stc_gfx_matrix_stack_end(&irodeo_gfx_state.matrix_stack).ref = matrix;
	irodeo_gfx_state.matrix_stack_top = matrix;
}

rodeo_math_mat4_t
rodeo_gfx_matrix_get(void)
{
		//return *stc_gfx_matrix_stack_top(&irodeo_gfx_state.matrix_stack);
		return irodeo_gfx_state.matrix_stack_top;
}

void
rodeo_gfx_matrix_push(void)
{
	stc_gfx_matrix_stack_push(
		&irodeo_gfx_state.matrix_stack,
		rodeo_gfx_matrix_get()
	);
}

void
rodeo_gfx_matrix_pop(void)
{
	// submit to render
	rodeo_gfx_renderer_flush();
	irodeo_gfx_state.matrix_stack_top = *stc_gfx_matrix_stack_top(&irodeo_gfx_state.matrix_stack);
	if(stc_gfx_matrix_stack_size(&irodeo_gfx_state.matrix_stack) > 0)
	{
		stc_gfx_matrix_stack_pop(&irodeo_gfx_state.matrix_stack);
		//stc_gfx_matrix_stack_push(&irodeo_gfx_state.matrix_stack, rodeo_math_mat4_identity());
	}
}

uint32_t
rodeo_gfx_matrix_size(void)
{
	return (uint32_t)stc_gfx_matrix_stack_size(&irodeo_gfx_state.matrix_stack);
}

uint32_t
rodeo_gfx_matrix_capacity(void)
{
	return (uint32_t)stc_gfx_matrix_stack_capacity(&irodeo_gfx_state.matrix_stack);
}

void
irodeo_gfx_camera_2d_init(void)
{
	irodeo_gfx_state.camera_2d_matrix = rodeo_math_mat4_identity();
}

void
irodeo_gfx_camera_2d_deinit(void)
{
	// nothing to do
}

void
rodeo_gfx_camera_2d_begin(rodeo_gfx_camera_2d_t camera)
{
	rodeo_gfx_renderer_flush();

    irodeo_gfx_state.camera_2d_matrix = rodeo_math_mat4_translate(irodeo_gfx_state.camera_2d_matrix, (rodeo_math_vec3_t){ .val.x = -camera.target.val.x, .val.y = -camera.target.val.y, .val.z = 0.0f });
	irodeo_gfx_state.camera_2d_matrix = rodeo_math_mat4_rotate(irodeo_gfx_state.camera_2d_matrix, camera.turns, (rodeo_math_vec3_t){ .val.z = 1 });
    //rodeo_math_mat4_t matRotation = MatrixRotate((rodeo_math_vec3_t){ 0.0f, 0.0f, 1.0f }, camera.rotation*DEG2RAD);
	irodeo_gfx_state.camera_2d_matrix = rodeo_math_mat4_scale(irodeo_gfx_state.camera_2d_matrix, (rodeo_math_vec3_t){ .val.x = camera.zoom, .val.y = camera.zoom, .val.z = 1.0f });
    //rodeo_math_mat4_t matScale = MatrixScale(camera.zoom, camera.zoom, 1.0f);
	irodeo_gfx_state.camera_2d_matrix = rodeo_math_mat4_translate(irodeo_gfx_state.camera_2d_matrix, (rodeo_math_vec3_t){ .val.x = camera.offset.val.x, .val.y = camera.offset.val.y });
    //rodeo_math_mat4_t matTranslation = MatrixTranslate(camera.offset.x, camera.offset.y, 0.0f);

	// build matrix
}

void
rodeo_gfx_camera_2d_end(void)
{
	rodeo_gfx_renderer_flush();

	irodeo_gfx_state.camera_2d_matrix = rodeo_math_mat4_identity();
}

bgfx_shader_handle_t
irodeo_gfx_shader_load(const cstr path)
{
	const char* path_cstr = cstr_str(&path);

	FILE *file = fopen(path_cstr, "rb");

	if(!file)
	{
		rodeo_log(
				rodeo_logLevel_error,
				"Shader file \"%s\" not found",
				path_cstr
				);
		return (bgfx_shader_handle_t)BGFX_INVALID_HANDLE;
	}

	fseek(file, 0, SEEK_END);
	int64_t file_size_temp = ftell(file);
	if(file_size_temp < 0)
	{
		rodeo_log(
				rodeo_logLevel_error,
				"Failed to get current file position of given stream(ftell() error)"
				);
		exit(EXIT_FAILURE);
	}
	if((file_size_temp + 1) > UINT32_MAX)
	{
		rodeo_log(
				rodeo_logLevel_error,
				"File size larger then what bgfx can allocate"
				);
		exit(EXIT_FAILURE);
	}
	uint32_t file_size = (uint32_t)file_size_temp;
	fseek(file, 0, SEEK_SET);


	const bgfx_memory_t *mem = bgfx_alloc(file_size + 1);
	fread(mem->data, 1, file_size, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	bgfx_shader_handle_t shader = bgfx_create_shader(mem);
	rodeo_log(
			rodeo_logLevel_info,
			"Shader loaded with idx: %"PRIu8"",
			shader.idx
			);

	return shader;
}

void
irodeo_gfx_render_buffer_transient_alloc(void)
{
	bgfx_alloc_transient_vertex_buffer(&irodeo_gfx_state.vertex_buffer_handle, mrodeo_vertex_size_max, &irodeo_gfx_state.vertex_layout);
	bgfx_alloc_transient_index_buffer(&irodeo_gfx_state.index_buffer_handle, mrodeo_index_size_max, false);
	irodeo_gfx_state.batched_vertices = (rodeo_gfx_vertex_t*)irodeo_gfx_state.vertex_buffer_handle.data;
	irodeo_gfx_state.batched_indices = (rodeo_gfx_index_t*)irodeo_gfx_state.index_buffer_handle.data;
}


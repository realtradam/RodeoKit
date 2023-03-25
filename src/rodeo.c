// -- internal --
// public
#include "rodeo.h"
#include "rodeo_types.h"
// private
#include "rodeo_internal.h"
#include "rodeo_internal_types.h"

// -- external --
#if __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"
//#define CGLM_FORCE_LEFT_HANDED
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
//#define CGLM_CLIPSPACE_INCLUDE_ALL
#include "cglm/cglm.h"

// -- system --
#include <time.h>


rodeo_texture_2d_t rodeo_texture_2d_default;


static irodeo_state_t state = {0};

void
rodeo_window_init(
	int screen_height,
	int screen_width,
	char* title
)
{
	state.window = NULL;
	state.screen_surface = NULL;
	state.screen_height = screen_height;
	state.screen_width = screen_width;
	state.frame_count = 0;

	rodeo_log(
		rodeo_loglevel_info,
		"Initializing SDL..."
	);
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		rodeo_log(
			rodeo_loglevel_error,
			"Failed to initialize SDL. SDL_Error: %s",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_loglevel_info,
		"Success initializing SDL"
	);

	rodeo_log(
		rodeo_loglevel_info,
		"Initializing SDL window..."
	);
	state.window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN
			);
	if(state.window == NULL)
	{
		rodeo_log(
			rodeo_loglevel_error,
			"Failed creating SDL window. SDL_Error: %s",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_loglevel_info,
		"Success initializing SDL window"
	);

#if !__EMSCRIPTEN__
	rodeo_log(
		rodeo_loglevel_info,
		"SDL setting up driver specific information..."
	);
	SDL_VERSION(&state.wmi.version);
	if(
		!SDL_GetWindowWMInfo(
			state.window,
			&state.wmi  
		)
	)
	{
		rodeo_log(
			rodeo_loglevel_error,
			"SDL failed to get driver specific information. SDL Error: %s", SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_loglevel_info,
		"Success getting driver specific information"
	);
	bgfx_render_frame(-1);
#endif


	bgfx_platform_data_t pd;
	memset(&pd, 0, sizeof(bgfx_platform_data_t));

#if !__EMSCRIPTEN__
	// x11
	pd.ndt = state.wmi.info.x11.display;
	pd.nwh = (void*)(uintptr_t)state.wmi.info.x11.window;
#else
	// web
	pd.nwh = (void*)"#canvas";
#endif

	bgfx_init_t init = {0};
	bgfx_init_ctor(&init);
	init.type = BGFX_RENDERER_TYPE_COUNT; // auto determine renderer
	//init.type = BGFX_RENDERER_TYPE_OPENGL; // force opengl renderer
	init.resolution.width = state.screen_width;
	init.resolution.height = state.screen_height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.platformData = pd;
	bgfx_init(&init);

	bgfx_set_debug(BGFX_DEBUG_TEXT);

	//bgfx_set_state(BGFX_STATE_CULL_CCW, 0);

	bgfx_set_view_clear(
		0,
		BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
		0x443355FF,
		1.0f,
		0
	);
	bgfx_set_view_rect(0, 0, 0, state.screen_width, state.screen_height);

	rodeo_log(rodeo_loglevel_info, "Setting up default render pipeline...");
	// set up vertex layout
	mrodeo_bgfx_vertex_layout_do(&state.vertex_layout)
	{
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_UINT8, true, true);
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_TEXCOORD0, 3, BGFX_ATTRIB_TYPE_FLOAT, false, false);
	}

	state.vertex_buffer_handle = bgfx_create_dynamic_vertex_buffer(mrodeo_vertex_size_max, &state.vertex_layout, BGFX_BUFFER_NONE);

	state.index_buffer_handle = bgfx_create_dynamic_index_buffer((mrodeo_vertex_size_max / 4) * 6, BGFX_BUFFER_NONE);

	// load shaders
	rodeo_string_t shader_path = rodeo_string_create("???");
	switch(bgfx_get_renderer_type()) {
        case BGFX_RENDERER_TYPE_NOOP:
			rodeo_log(
				rodeo_loglevel_error,
				"BGFX failed to get determine an appropriate renderer"
			);
			exit(EXIT_FAILURE);
        case BGFX_RENDERER_TYPE_OPENGLES:
			rodeo_string_set(
				&shader_path,
				"shaders/100_es/"
			);
			break;
        case BGFX_RENDERER_TYPE_VULKAN:
			rodeo_string_set(
				&shader_path,
				"shaders/spirv/"
			);
			break;
		default:
			rodeo_log(
				rodeo_loglevel_error,
				"No shaders implemented for BGFX renderer chosen"
			);
			exit(EXIT_FAILURE);
    }
	rodeo_string_t vertex_shader_path = rodeo_string_create("simple.vertex.bin");
	rodeo_string_t fragment_shader_path = rodeo_string_create("simple.fragment.bin");

	rodeo_string_prepend(
		&vertex_shader_path,
		shader_path
	);
	rodeo_string_prepend(
		&fragment_shader_path,
		shader_path
	);

	state.vertex_shader = irodeo_shader_load(vertex_shader_path);
	state.fragment_shader = irodeo_shader_load(fragment_shader_path);
	state.program_shader = bgfx_create_program(
		state.vertex_shader,
		state.fragment_shader,
		true
	);
	rodeo_log(
		rodeo_loglevel_info,
		"Default render pipeline finished setup"
	);

	//bgfx_texture_handle_t default_bgfx_texture = rodeo_texture_2d_create_default();

	rodeo_texture_2d_default.internal_texture = malloc(sizeof(irodeo_texture_internal_t));

	// used for binding textures to shader uniforms
	state.texture_uniforms[0] = bgfx_create_uniform("default_texture", BGFX_UNIFORM_TYPE_SAMPLER, 1);
	state.texture_uniforms[1] = bgfx_create_uniform("texture_0", BGFX_UNIFORM_TYPE_SAMPLER, 1);

	{
		// represents 1 pixel sized white texture
		//const rodeo_RGBA8_t default_texture_data = 
		//{
		//	.red =   0xff,
		//	.green = 0xff,
		//	.blue =  0xff,
		//	.alpha = 0xff,
		//};
		const uint8_t default_texture_data[] = {
			0xff, 0x00, 0xff, 0xff,
			0xff, 0xff, 0x00, 0xff,
			0x00, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff,
			//0xff, 0xff, 0xff, 0xff,
		};

		rodeo_texture_2d_default.internal_texture->texture_bgfx = 
			bgfx_create_texture_2d(
				2,
				2,
				false,
				0,
				BGFX_TEXTURE_FORMAT_RGBA8,
				BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_MAG_POINT,
				bgfx_copy(&default_texture_data, sizeof(default_texture_data))
			);
	}

	state.end_frame = SDL_GetPerformanceCounter();
}

void
rodeo_window_deinit(void)
{
	free(rodeo_texture_2d_default.internal_texture);
	bgfx_destroy_dynamic_index_buffer(state.index_buffer_handle);
	bgfx_destroy_dynamic_vertex_buffer(state.vertex_buffer_handle);
	bgfx_destroy_program(state.program_shader);
	bgfx_shutdown();
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}

void
rodeo_frame_begin(void)
{
	//vec3 eye = {0.0f, 0.0f, -35.0f};
	//vec3 center = {0.0f, 0.0f, 0.0f};
	//vec3 up = {0, 1, 0};
	mat4 view;
	//glm_lookat(eye, center, up, view);
	glm_mat4_identity(view);

	mat4 proj;
	//glm_perspective(glm_rad(60.f), 640.f / 480.f, 0.1f, 100.0f, proj);

	// TODO: figure out if why 'zo' is correct
	// but 'no' is incorrect
	glm_ortho_rh_zo( 
		0,
		state.screen_width,
		state.screen_height,
		0,
		// near
		-0.1f,
		// far
		100.0f,
		proj
	);
	bgfx_set_view_transform(0, view, proj);
	bgfx_set_view_rect(0, 0, 0, state.screen_width, state.screen_height);
	bgfx_touch(0);
	state.start_frame = state.end_frame;
}

void
rodeo_frame_end(void)
{
	rodeo_renderer_flush();

	bgfx_frame(false);

	while(SDL_PollEvent(&state.sdl_event))
	{
		if(state.sdl_event.type == SDL_QUIT)
		{
			state.quit = true;
		}
	}
	#ifndef __EMSCRIPTEN__
		irodeo_frame_stall();
	#endif
	state.frame_count += 1;
	state.end_frame = SDL_GetPerformanceCounter();
	state.frame_time = ((float)(state.end_frame - state.start_frame) * 1000.0f / (float)SDL_GetPerformanceFrequency());
}

void
rodeo_mainloop_run(
	rodeo_mainLoop_function mainloop_func
)
{
	#if __EMSCRIPTEN__
		emscripten_set_main_loop(mainloop_func, 0, 1);
	#else
		while(!rodeo_window_check_quit())
		{ 
			mainloop_func();
		} 
	#endif
}

bool
rodeo_window_check_quit(void)
{
	return state.quit;
}

void
rodeo_set_quit(bool quit)
{
	state.quit = quit;
}

void
rodeo_debug_text_draw(u_int16_t x, u_int16_t y, const char *format, ...)
{
	mrodeo_vargs_do(format)
	{
		bgfx_dbg_text_vprintf(x, y, 0x65, format, vargs);
	}
}

rodeo_string_t
rodeo_renderer_name_get(void)
{
	return rodeo_string_create(bgfx_get_renderer_name(bgfx_get_renderer_type()));
}

void
rodeo_renderer_flush(void)
{
	// set default texture
	bgfx_set_texture(
		0,
		state.texture_uniforms[0],
		rodeo_texture_2d_default.internal_texture->texture_bgfx,
		UINT32_MAX
	);
	if(state.active_texture_p != NULL)
	{
		// set dynamic texture
		bgfx_set_texture(
			1,
			state.texture_uniforms[1],
			*state.active_texture_p,
			UINT32_MAX
		);
	}
	else
	{
		// set to default if none exists
		bgfx_set_texture(
			1,
			state.texture_uniforms[1],
			rodeo_texture_2d_default.internal_texture->texture_bgfx,
			UINT32_MAX
		);
	}

	if(state.vertex_size > 0)
	{
		// upload remaining batched vertices
		bgfx_set_dynamic_vertex_buffer(0, state.vertex_buffer_handle, 0, state.vertex_size);
		const bgfx_memory_t* vbm = bgfx_copy(state.batched_vertices, sizeof(rodeo_vertex_t) * state.vertex_size);
		bgfx_update_dynamic_vertex_buffer(state.vertex_buffer_handle,  0, vbm);

		// upload remaining batched indices
		bgfx_set_dynamic_index_buffer(state.index_buffer_handle, 0, state.index_size);
		const bgfx_memory_t* ibm = bgfx_copy(state.batched_indices, sizeof(uint16_t) * state.index_size);
		bgfx_update_dynamic_index_buffer(state.index_buffer_handle, 0, ibm);

		bgfx_set_state(
			BGFX_STATE_CULL_CW |
			BGFX_STATE_WRITE_RGB |
			BGFX_STATE_WRITE_A |
			//BGFX_STATE_DEPTH_TEST_LESS |
			//BGFX_STATE_MSAA |
			BGFX_STATE_BLEND_ALPHA,
			0
		);

		// submit vertices & batches
		bgfx_submit(0, state.program_shader, 0, BGFX_DISCARD_ALL);

		// reset arrays
		state.vertex_size = 0;
		state.index_size = 0;
		state.index_count = 0;
	}
	state.active_texture_p = NULL;
}

void
rodeo_rectangle_draw(
	rodeo_rectangle_t rectangle,
	rodeo_RGBAFloat_t color
)
{
	rodeo_texture_2d_draw(
		(rodeo_rectangle_t){ 0, 0, 1, 1 },
		rectangle,
		color,
		NULL
	);
	/*
	const rodeo_BGRA8_t bgra = rodeo_RGBA8_to_BGRA8(
		rodeo_RGBAFloat_to_RGBA8(color)
	);


	if(state.vertex_size < mrodeo_vertex_size_max)
	{
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = rectangle.width + rectangle.x,
				.y = rectangle.height + rectangle.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = rectangle.width + rectangle.x,
				.y = rectangle.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = rectangle.x,
				.y = rectangle.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = rectangle.x,
				.y = rectangle.height + rectangle.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
			};
		state.vertex_size += 1;

		int indices[] =
		{
			0, 1, 3,
			1, 2, 3
			//2, 1, 0,
			//2, 3, 1
		};
		state.batched_indices[state.index_size] = state.index_count + indices[0];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[1];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[2];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[3];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[4];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[5];
		state.index_size += 1;
		state.index_count += 4;
	}

	if(state.vertex_size >= mrodeo_vertex_size_max)
	{
		rodeo_renderer_flush();
	}
	*/
}


rodeo_texture_2d_t
rodeo_texture_2d_create_from_RGBA8(
	const uint32_t width,
	const uint32_t height,
	const uint8_t memory[]
)
{
	rodeo_texture_2d_t texture;
	texture.internal_texture = malloc(sizeof(irodeo_texture_internal_t));
	texture.internal_texture->texture_bgfx = bgfx_create_texture_2d(
		width,
		height,
		false,
		1,
		BGFX_TEXTURE_FORMAT_RGBA8,
		BGFX_TEXTURE_NONE,
		bgfx_copy(&memory, width * height * 4)
	);

	return texture;
}

void
rodeo_texture_2d_draw(
	const rodeo_rectangle_t source,
	const rodeo_rectangle_t destination,
	const rodeo_RGBAFloat_t color,
	const rodeo_texture_2d_t *texture
)
{
	// gonna need to change the shader pipeline
	// to also accept textures
	const rodeo_BGRA8_t bgra = rodeo_RGBA8_to_BGRA8(
		rodeo_RGBAFloat_to_RGBA8(color)
	);
	float texture_uniform_slot = 0.0;

	// if not using texture: use default instead
	// otherwise check what current texture is active
	//	if none or the same: set it
	//	if different: flush and then set it
	if(texture != NULL)
	{
		if(state.active_texture_p != NULL)
		{
			if(&texture->internal_texture->texture_bgfx != state.active_texture_p)
			{
				rodeo_renderer_flush();
			}
		}
		texture_uniform_slot = 1.0;
		state.active_texture_p = &texture->internal_texture->texture_bgfx;
	}


	if(state.vertex_size < mrodeo_vertex_size_max)
	{
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = destination.width + destination.x,
				.y = destination.height + destination.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
				.texture_id = texture_uniform_slot,
				.texture_x = 1,//source.width + source.x,
				.texture_y = 1,//source.height + source.y,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = destination.width + destination.x,
				.y = destination.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
				.texture_id = texture_uniform_slot,
				.texture_x = 1,//source.width + source.x,
				.texture_y = 0,//source.y,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = destination.x,
				.y = destination.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
				.texture_id = texture_uniform_slot,
				.texture_x = 0,//source.x,
				.texture_y = 0,//source.y,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{
				.x = destination.x,
				.y = destination.height + destination.y,
				//.z = 0.0f,
				.bgra = bgra.bgra,
				.texture_id = texture_uniform_slot,
				.texture_x = 0,//source.x,
				.texture_y = 1,//source.height + source.y,
			};
		state.vertex_size += 1;

		int indices[] =
		{
			0, 1, 3,
			1, 2, 3
			//2, 1, 0,
			//2, 3, 1
		};
		state.batched_indices[state.index_size] = state.index_count + indices[0];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[1];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[2];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[3];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[4];
		state.index_size += 1;
		state.batched_indices[state.index_size] = state.index_count + indices[5];
		state.index_size += 1;
		state.index_count += 4;
	}

	if(state.vertex_size >= mrodeo_vertex_size_max)
	{
		rodeo_renderer_flush();
	}
}


/*
rodeo_texture_2d_p
rodeo_texture_2d_create_from_path(rodeo_string_t path)
{
	// call load file into data
	// then call create_from_data variant
}

void
rodeo_texture_2d_destroy(rodeo_texture_2d_t *texture)
{

}
*/
bgfx_shader_handle_t
irodeo_shader_load(const rodeo_string_t path)
{
	const char* path_cstr = rodeo_string_to_constcstr(&path);
	bgfx_shader_handle_t invalid = BGFX_INVALID_HANDLE;

	FILE *file = fopen(path_cstr, "rb");

	if(!file)
	{
		rodeo_log(
			rodeo_loglevel_error,
			"Shader file \"%s\" not found",
			path_cstr
		);
		return invalid;
	}

	fseek(file, 0, SEEK_END);
	int64_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx_memory_t *mem = bgfx_alloc(file_size + 1);
	fread(mem->data, 1, file_size, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	bgfx_shader_handle_t shader = bgfx_create_shader(mem);
	rodeo_log(
		rodeo_loglevel_info,
		"Shader loaded with idx: %"PRIu8"",
		shader.idx
	);

	return shader;
}

uint64_t
rodeo_frame_count_get(void)
{
	return state.frame_count;
}

float
rodeo_frame_time_get(void)
{
	return state.frame_time;
}

float
rodeo_frame_persecond_get(void)
{
	return 1.0f / (rodeo_frame_time_get() / 1000.0f);
}

void
rodeo_frame_limit_set(uint32_t limit)
{
	#ifdef __EMSCRIPTEN__
		rodeo_log(
			rodeo_loglevel_warning,
			"Framerate limit cannot be set on web platform. Limit is enforced by platform to 60fps"
		);
	#else
		state.frame_limit = limit;
	#endif
}

uint32_t
rodeo_frame_limit_get(void)
{
	#ifdef __EMSCRIPTEN__
		return 60;
	#else
		return state.frame_limit;
	#endif
}

// measures how much time there is left in the remaining frame until
// the frame target time is reached. If we surpassed the target time
// then this will be negative
float
irodeo_frame_remaining_get(void)
{
	#ifdef __EMSCRIPTEN__
		float target = 60.0f;
	#else
		float target = (float)rodeo_frame_limit_get();
	#endif

	float result = (1/target * 1000.0f) - ((float)(SDL_GetPerformanceCounter() - state.start_frame) / (float)SDL_GetPerformanceFrequency() * 1000.0f);

	return result;
}

// used internally at the end of every frame to fill for time
// in order to reach the desired framerate
void
irodeo_frame_stall(void)
{
	// if no frame limit then run as fast as possible
	if(rodeo_frame_limit_get() == 0)
	{
		return;
	}

	// sleep isnt perfectly accurate so we sleep for a slightly shorter
	// amount of time
	float stall_time = irodeo_frame_remaining_get();
	if(stall_time > 0.0005)
	{
		SDL_Delay(stall_time * 0.9995);
	}

	// then we spinlock for the small remaining amount of time
	stall_time = irodeo_frame_remaining_get();
	while(stall_time > 0.0005) {
		stall_time = irodeo_frame_remaining_get();
	}
}


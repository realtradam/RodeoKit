// -- internal --
// public
#include "rodeo.h"
#include "rodeo_types.h"
#include "rodeo/input.h"
// private
#include "rodeo_internal.h"
#include "rodeo_internal_types.h"

// -- external --
#if __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_syswm.h"
#include "bgfx/c99/bgfx.h"
/*#define CGLM_FORCE_LEFT_HANDED*/
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
/*#define CGLM_CLIPSPACE_INCLUDE_ALL*/
#include "cglm/cglm.h"
#include "stc/crandom.h"

// -- system --
#include <time.h>

static irodeo_state_t state = {0};

void
rodeo_window_init(
	uint16_t screen_height,
	uint16_t screen_width,
	cstr title
)
{
	state.window = NULL;
	state.screen_surface = NULL;
	state.screen_height = screen_height;
	state.screen_width = screen_width;
	state.frame_count = 0;

	rodeo_log(
		rodeo_logLevel_info,
		"Initializing SDL..."
	);

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to initialize SDL. SDL_Error: %s",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_logLevel_info,
		"Success initializing SDL"
	);

	rodeo_log(
		rodeo_logLevel_info,
		"Initializing SDL window..."
	);
	state.window = SDL_CreateWindow(
			cstr_str(&title),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN
			);
	if(state.window == NULL)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed creating SDL window. SDL_Error: %s",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_logLevel_info,
		"Success initializing SDL window"
	);

#if !__EMSCRIPTEN__
	rodeo_log(
		rodeo_logLevel_info,
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
			rodeo_logLevel_error,
			"SDL failed to get driver specific information. SDL Error: %s", SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	rodeo_log(
		rodeo_logLevel_info,
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

	rodeo_log(rodeo_logLevel_info, "Setting up default render pipeline...");
	// set up vertex layout
	mrodeo_bgfx_vertex_layout_do(&state.vertex_layout)
	{
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_TEXCOORD0, 2, BGFX_ATTRIB_TYPE_FLOAT, false, false);
		bgfx_vertex_layout_add(&state.vertex_layout, BGFX_ATTRIB_TEXCOORD1, 1, BGFX_ATTRIB_TYPE_FLOAT, false, false);
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

	state.vertex_shader = irodeo_shader_load(vertex_shader_path);
	state.fragment_shader = irodeo_shader_load(fragment_shader_path);
	state.program_shader = bgfx_create_program(
		state.vertex_shader,
		state.fragment_shader,
		true
	);
	rodeo_log(
		rodeo_logLevel_info,
		"Default render pipeline finished setup"
	);

	//bgfx_texture_handle_t default_bgfx_texture = rodeo_texture_2d_create_default();

	state.default_texture.internal_texture = malloc(sizeof(irodeo_texture_internal_t));

	// used for binding textures to shader uniforms
	state.texture_uniforms[0] = bgfx_create_uniform("default_texture", BGFX_UNIFORM_TYPE_SAMPLER, 1);
	state.texture_uniforms[1] = bgfx_create_uniform("texture_0", BGFX_UNIFORM_TYPE_SAMPLER, 1);

	{
		// represents 1 pixel sized white texture
		const uint8_t default_texture_data[] = {
			//red, blue, green, alpha
			0xff, 0xff, 0xff, 0xff,
		};

		state.default_texture.internal_texture->texture_bgfx = 
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
		state.default_texture.width = 1;
		state.default_texture.height = 1;

		state.active_texture_p = &state.default_texture.internal_texture->texture_bgfx;
	}

	rodeo_random_seed_set(SDL_GetTicks64());

	state.end_frame = SDL_GetPerformanceCounter();
}

void
rodeo_window_deinit(void)
{
	free(state.default_texture.internal_texture);

	//bgfx_destroy_dynamic_index_buffer(state.index_buffer_handle);
	//bgfx_destroy_dynamic_vertex_buffer(state.vertex_buffer_handle);
	bgfx_destroy_program(state.program_shader);
	bgfx_shutdown();

	SDL_DestroyWindow(state.window);
	SDL_Quit();
}

uint16_t
rodeo_screen_width_get(void)
{
	return state.screen_width;
}

uint16_t
rodeo_screen_height_get(void)
{
	return state.screen_height;
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
		(float)state.screen_width,
		(float)state.screen_height,
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

	irodeo_render_buffer_transient_alloc();

	state.quit = rodeo_input_events_poll();

	state.start_frame = state.end_frame;
}

void
rodeo_frame_end(void)
{
	rodeo_renderer_flush();

	bgfx_frame(false);

	#ifndef __EMSCRIPTEN__
		irodeo_frame_stall();
	#endif
	state.frame_count += 1;
	state.end_frame = SDL_GetPerformanceCounter();
	state.frame_time = ((float)(state.end_frame - state.start_frame) * 1000.0f / (float)SDL_GetPerformanceFrequency());
}

void
irodeo_render_buffer_transient_alloc(void)
{
	bgfx_alloc_transient_vertex_buffer(&state.vertex_buffer_handle, mrodeo_vertex_size_max, &state.vertex_layout);
	bgfx_alloc_transient_index_buffer(&state.index_buffer_handle, mrodeo_index_size_max, false);
	state.batched_vertices = (rodeo_vertex_t*)state.vertex_buffer_handle.data;
	state.batched_indices = (irodeo_index_type_t*)state.index_buffer_handle.data;
}

void
rodeo_mainLoop_run(
	rodeo_mainLoop_function main_loop_func
)
{
	#if __EMSCRIPTEN__
		emscripten_set_main_loop(main_loop_func, 0, 1);
	#else
		while(!rodeo_window_quit_get())
		{ 
			main_loop_func();
		} 
	#endif
}

bool
rodeo_window_quit_get(void)
{
	return state.quit;
}

void
rodeo_window_quit_set(bool quit)
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

cstr
rodeo_renderer_name_get(void)
{
	return cstr_from(
		bgfx_get_renderer_name(bgfx_get_renderer_type())
	);
}

void
rodeo_renderer_flush(void)
{
	// set default texture
	bgfx_set_texture(
		0,
		state.texture_uniforms[0],
		rodeo_texture_2d_default_get()->internal_texture->texture_bgfx,
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
			rodeo_texture_2d_default_get()->internal_texture->texture_bgfx,
			UINT32_MAX
		);
	}

	if(state.vertex_size > 0)
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
		bgfx_set_transient_vertex_buffer(0, &state.vertex_buffer_handle, 0, state.vertex_size);
		//const bgfx_memory_t* vbm = bgfx_copy(state.batched_vertices, sizeof(rodeo_vertex_t) * state.vertex_size);
		//bgfx_update_dynamic_vertex_buffer(state.vertex_buffer_handle,  0, vbm);

		// upload remaining batched indices
		bgfx_set_transient_index_buffer(&state.index_buffer_handle, 0, state.index_size);
		//bgfx_set_dynamic_index_buffer(state.index_buffer_handle, 0, state.index_size);
		//const bgfx_memory_t* ibm = bgfx_copy(state.batched_indices, sizeof(uint16_t) * state.index_size);
		//bgfx_update_dynamic_index_buffer(state.index_buffer_handle, 0, ibm);


		// submit vertices & batches
		bgfx_submit(0, state.program_shader, 0, BGFX_DISCARD_NONE);

		// reset arrays
		state.vertex_size = 0;
		state.index_size = 0;
		state.index_count = 0;

		// allocate new buffers
		irodeo_render_buffer_transient_alloc();
	}
	state.active_texture_p = NULL;
}

const rodeo_texture_2d_t*
rodeo_texture_2d_default_get(void)
{
	return &state.default_texture;
}

rodeo_texture_2d_t
rodeo_texture_2d_create_from_RGBA8(
	const uint16_t width,
	const uint16_t height,
	const uint8_t memory[]
)
{
	rodeo_texture_2d_t texture;
	texture.internal_texture = malloc(sizeof(irodeo_texture_internal_t));
	texture.internal_texture->texture_bgfx =
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
rodeo_texture_2d_destroy(rodeo_texture_2d_t *texture)
{
	bgfx_destroy_texture(texture->internal_texture->texture_bgfx);
	free(texture->internal_texture);
}

void
rodeo_rectangle_draw(
	const rodeo_rectangle_t *rectangle,
	const rodeo_color_RGBAFloat_t *color
)
{
	rodeo_texture_2d_draw(
		rectangle,
		NULL,
		color,
		NULL
	);
}

void
rodeo_texture_2d_draw(
	// cant be NULL
	const rodeo_rectangle_t *destination,
	// default: entire texture
	const rodeo_rectangle_t *source,
	// default: white
	const rodeo_color_RGBAFloat_t *color,
	// default: default texture
	const rodeo_texture_2d_t *texture
)
{
	// whether to use default or custom texture
	float texture_uniform_slot = 0.0;

	rodeo_rectangle_t source_applied;
	if(source != NULL && texture != NULL)
	{
		source_applied = (rodeo_rectangle_t){
			.x = source->x / (float)texture->width,
			.y = source->y / (float)texture->height,
			.width = source->width / (float)texture->width,
			.height = source->height / (float)texture->height,
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

	rodeo_color_RGBAFloat_t color_applied;
	if(color != NULL)
	{
		color_applied = *color;
	}
	else
	{
		color_applied = (rodeo_color_RGBAFloat_t){
			{ 1.0f, 1.0f, 1.0f, 1.0f }
		};
	}

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
				.x = destination->width + destination->x,
				.y = destination->height + destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.width + source_applied.x,
				.texture_y = source_applied.height + source_applied.y,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{ 
				.x = destination->width + destination->x,
				.y = destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.width + source_applied.x,
				.texture_y = source_applied.y,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{ 
				.x = destination->x,
				.y = destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.x,
				.texture_y = source_applied.y,
			};
		state.vertex_size += 1;
		state.batched_vertices[state.vertex_size] =
			(rodeo_vertex_t)
			{ 
				.x = destination->x,
				.y = destination->height + destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.x,
				.texture_y = source_applied.height + source_applied.y,
			};
		state.vertex_size += 1;

		irodeo_index_type_t indices[] =
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

rodeo_texture_2d_t
rodeo_texture_2d_create_from_path(cstr path)
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
		return (rodeo_texture_2d_t){0};
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
		return (rodeo_texture_2d_t){0};
	}

	// load the pixel data into our own texture
	rodeo_texture_2d_t texture = rodeo_texture_2d_create_from_RGBA8(
		(uint16_t)converted_surface->w,
		(uint16_t)converted_surface->h,
		converted_surface->pixels
	);

	SDL_FreeSurface(surface);
	SDL_FreeSurface(converted_surface);

	return texture;
}

bgfx_shader_handle_t
irodeo_shader_load(const cstr path)
{
	const char* path_cstr = cstr_str(&path);
	bgfx_shader_handle_t invalid = BGFX_INVALID_HANDLE;

	FILE *file = fopen(path_cstr, "rb");

	if(!file)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Shader file \"%s\" not found",
			path_cstr
		);
		return invalid;
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
rodeo_frame_perSecond_get(void)
{
	return 1.0f / (rodeo_frame_time_get() / 1000.0f);
}

void
rodeo_frame_limit_set(uint32_t limit)
{
	#ifdef __EMSCRIPTEN__
		rodeo_log(
			rodeo_logLevel_warning,
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

void
irodeo_random_seed_set(stc64_t seed)
{
	state.random_seed = seed;
}

stc64_t*
irodeo_random_seed_get(void)
{
	return &state.random_seed;
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
		SDL_Delay((uint32_t)(stall_time * 0.9995));
	}

	// then we spinlock for the small remaining amount of time
	stall_time = irodeo_frame_remaining_get();
	while(stall_time > 0.0005) {
		stall_time = irodeo_frame_remaining_get();
	}
}


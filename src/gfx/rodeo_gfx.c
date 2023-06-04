
// -- internal --
// public
#include "rodeo.h" // TODO remove this
#include "rodeo/gfx.h"
#include "rodeo/window.h"
#include "rodeo/log.h"
// private
#include "gfx/irodeo_gfx.h"
#include "window/irodeo_window.h"
#include "rodeo_config.h"

// -- external --
#include "bgfx/c99/bgfx.h"
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
#include "cglm/cglm.h"
#include "SDL_image.h"
#include "SDL.h" // used for timing, need to replace in this file with BGFX at some point

static irodeo_gfx_state_t irodeo_gfx_state = {0};

void
rodeo_gfx_init(void)
{

#ifdef __EMSCRIPTEN__
	bgfx_render_frame(-1);
#endif

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
	init.resolution.width = rodeo_window_screen_height_get();
	init.resolution.height = rodeo_window_screen_width_get();
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.platformData = pd;
	bgfx_init(&init);

	bgfx_set_debug(BGFX_DEBUG_TEXT);

	//bgfx_set_state(BGFX_STATE_CULL_CCW, 0);
	
	//bgfx_dbg_text_clear(0x65, false);

	bgfx_set_view_clear(
		0,
		BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
		0x443355FF,
		1.0f,
		0
	);
	bgfx_set_view_rect(0, 0, 0, rodeo_window_screen_width_get(), rodeo_window_screen_height_get());

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

	irodeo_gfx_state.default_texture.internal_texture = malloc(sizeof(irodeo_gfx_texture_internal_t));

	// used for binding textures to shader uniforms
	irodeo_gfx_state.texture_uniforms[0] = bgfx_create_uniform("default_texture", BGFX_UNIFORM_TYPE_SAMPLER, 1);
	irodeo_gfx_state.texture_uniforms[1] = bgfx_create_uniform("texture_0", BGFX_UNIFORM_TYPE_SAMPLER, 1);

	{
		// represents 1 pixel sized white texture
		const uint8_t default_texture_data[] = {
			//red, blue, green, alpha
			0xff, 0xff, 0xff, 0xff,
		};

		irodeo_gfx_state.default_texture.internal_texture->texture_bgfx = 
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

		irodeo_gfx_state.active_texture_p = &irodeo_gfx_state.default_texture.internal_texture->texture_bgfx;
	}

	SDL_SetWindowResizable(irodeo_window_get(), true);

	bgfx_reset(
		(uint32_t)rodeo_window_screen_width_get(),
		(uint32_t)rodeo_window_screen_height_get(),
		//BGFX_RESET_MSAA_X16 | BGFX_RESET_MAXANISOTROPY,
		BGFX_RESET_VSYNC,
		BGFX_TEXTURE_FORMAT_COUNT
	);

	rodeo_random_seed_set(SDL_GetTicks64());

	irodeo_gfx_state.frame_end = (uint32_t)SDL_GetPerformanceCounter();
}

void
rodeo_gfx_deinit(void)
{

	free(irodeo_gfx_state.default_texture.internal_texture);

	bgfx_destroy_program(irodeo_gfx_state.program_shader);
	bgfx_shutdown();
}

void
rodeo_gfx_frame_begin(void)
{
	//vec3 eye = {0.0f, 0.0f, -35.0f};
	//vec3 center = {0.0f, 0.0f, 0.0f};
	//vec3 up = {0, 1, 0};
	
	//glm_lookat(eye, center, up, view);
	
	glm_mat4_identity(irodeo_gfx_state.view_matrix);

	//glm_perspective(glm_rad(60.f), 640.f / 480.f, 0.1f, 100.0f, proj);

	// TODO: figure out if why 'zo' is correct
	// but 'no' is incorrect
	glm_ortho_rh_zo( 
		0,
		(float)rodeo_window_screen_width_get(),
		(float)rodeo_window_screen_height_get(),
		0,
		// near
		-0.1f,
		// far
		100.0f,
		irodeo_gfx_state.proj_matrix
	);

	bgfx_set_view_transform(0, irodeo_gfx_state.view_matrix, irodeo_gfx_state.proj_matrix);
	bgfx_set_view_rect(0, 0, 0, rodeo_window_screen_width_get(), rodeo_window_screen_height_get());
	bgfx_touch(0);

	irodeo_gfx_render_buffer_transient_alloc();

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

void
rodeo_gfx_renderer_flush(void)
{
	// set default texture
	bgfx_set_texture(
		0,
		irodeo_gfx_state.texture_uniforms[0],
		rodeo_gfx_texture_2d_default_get()->internal_texture->texture_bgfx,
		UINT32_MAX
	);
	if(irodeo_gfx_state.active_texture_p != NULL)
	{
		// set dynamic texture
		bgfx_set_texture(
			1,
			irodeo_gfx_state.texture_uniforms[1],
			*irodeo_gfx_state.active_texture_p,
			UINT32_MAX
		);
	}
	else
	{
		// set to default if none exists
		bgfx_set_texture(
			1,
			irodeo_gfx_state.texture_uniforms[1],
			rodeo_gfx_texture_2d_default_get()->internal_texture->texture_bgfx,
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


		// submit vertices & batches
		bgfx_submit(0, irodeo_gfx_state.program_shader, 0, BGFX_DISCARD_NONE);

		// reset arrays
		irodeo_gfx_state.vertex_size = 0;
		irodeo_gfx_state.index_size = 0;
		irodeo_gfx_state.index_count = 0;

		// allocate new buffers
		irodeo_gfx_render_buffer_transient_alloc();
	}
	irodeo_gfx_state.active_texture_p = NULL;
}

const rodeo_gfx_texture_2d_t*
rodeo_gfx_texture_2d_default_get(void)
{
	return &irodeo_gfx_state.default_texture;
}

rodeo_gfx_texture_2d_t
rodeo_gfx_texture_2d_create_from_RGBA8(
	const uint16_t width,
	const uint16_t height,
	const uint8_t memory[]
)
{
	rodeo_gfx_texture_2d_t texture;
	texture.internal_texture = malloc(sizeof(irodeo_gfx_texture_internal_t));
	bgfx_copy(memory, (uint32_t)width * (uint32_t)height * sizeof(uint8_t) * 4);
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
rodeo_gfx_texture_2d_destroy(rodeo_gfx_texture_2d_t *texture)
{
	bgfx_destroy_texture(texture->internal_texture->texture_bgfx);
	free(texture->internal_texture);
}

void
rodeo_gfx_rectangle_draw(
	const rodeo_rectangle_t *rectangle,
	const rodeo_color_RGBAFloat_t *color
)
{
	rodeo_gfx_texture_2d_draw(
		rectangle,
		NULL,
		color,
		NULL
	);
}

void
rodeo_gfx_texture_2d_draw(
	// cant be NULL
	const rodeo_rectangle_t *destination,
	// default: entire texture
	const rodeo_rectangle_t *source,
	// default: white
	const rodeo_color_RGBAFloat_t *color,
	// default: default texture
	const rodeo_gfx_texture_2d_t *texture
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
		if(irodeo_gfx_state.active_texture_p != NULL)
		{
			if(&texture->internal_texture->texture_bgfx != irodeo_gfx_state.active_texture_p)
			{
				rodeo_gfx_renderer_flush();
			}
		}
		texture_uniform_slot = 1.0;
		irodeo_gfx_state.active_texture_p = &texture->internal_texture->texture_bgfx;
	}


	if(irodeo_gfx_state.vertex_size < mrodeo_vertex_size_max)
	{
		irodeo_gfx_state.batched_vertices[irodeo_gfx_state.vertex_size] =
			(rodeo_gfx_vertex_t)
			{ 
				.x = destination->width + destination->x,
				.y = destination->height + destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.width + source_applied.x,
				.texture_y = source_applied.height + source_applied.y,
			};
		irodeo_gfx_state.vertex_size += 1;
		irodeo_gfx_state.batched_vertices[irodeo_gfx_state.vertex_size] =
			(rodeo_gfx_vertex_t)
			{ 
				.x = destination->width + destination->x,
				.y = destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.width + source_applied.x,
				.texture_y = source_applied.y,
			};
		irodeo_gfx_state.vertex_size += 1;
		irodeo_gfx_state.batched_vertices[irodeo_gfx_state.vertex_size] =
			(rodeo_gfx_vertex_t)
			{ 
				.x = destination->x,
				.y = destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.x,
				.texture_y = source_applied.y,
			};
		irodeo_gfx_state.vertex_size += 1;
		irodeo_gfx_state.batched_vertices[irodeo_gfx_state.vertex_size] =
			(rodeo_gfx_vertex_t)
			{ 
				.x = destination->x,
				.y = destination->height + destination->y,
				//.z = 0.0f, 
				.color = color_applied,
				.texture_id = texture_uniform_slot,
				.texture_x = source_applied.x,
				.texture_y = source_applied.height + source_applied.y,
			};
		irodeo_gfx_state.vertex_size += 1;

		irodeo_index_type_t indices[] =
		{
			0, 1, 3,
			1, 2, 3
			//2, 1, 0,
			//2, 3, 1
		};
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = irodeo_gfx_state.index_count + indices[0];
		irodeo_gfx_state.index_size += 1;
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = irodeo_gfx_state.index_count + indices[1];
		irodeo_gfx_state.index_size += 1;
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = irodeo_gfx_state.index_count + indices[2];
		irodeo_gfx_state.index_size += 1;
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = irodeo_gfx_state.index_count + indices[3];
		irodeo_gfx_state.index_size += 1;
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = irodeo_gfx_state.index_count + indices[4];
		irodeo_gfx_state.index_size += 1;
		irodeo_gfx_state.batched_indices[irodeo_gfx_state.index_size] = irodeo_gfx_state.index_count + indices[5];
		irodeo_gfx_state.index_size += 1;
		irodeo_gfx_state.index_count += 4;
	}

	if(irodeo_gfx_state.vertex_size >= mrodeo_vertex_size_max)
	{
		rodeo_gfx_renderer_flush();
	}
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
	irodeo_gfx_state.batched_indices = (irodeo_index_type_t*)irodeo_gfx_state.index_buffer_handle.data;
}


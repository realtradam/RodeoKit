
// public internal
#include "rodeo.h"
#include "rodeo_math.h"
#include "rodeo_types.h"
// private internal
#include "private/rodeo_internal.h"
#include "private/rodeo_internal_types.h"
#include "private/rodeo_error.h"

// external
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

void
Rodeo__\
init_window(
	Rodeo__data_p *state_p,
	int screen_height,
	int screen_width,
	char* title
)
{
	*state_p = (Rodeo__data_p)malloc(sizeof(Rodeo__data_t));
	Rodeo__data_p state = *state_p;
	if(!state)
	{
		Rodeo__error_exit(
			RODEO__ERROR__UNINITIALIZED_STATE,
			__FUNCTION__,
			__LINE__,
			"Malloc failed to initialize state."
		);
	}
	state->window = NULL;
	state->screen_surface = NULL;
	state->screen_height = screen_height;
	state->screen_width = screen_width;

	printf("SDL_Init...\n");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	printf("done\n");

	printf("SDL_CreateWindow...\n");
	state->window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN
			);
	printf("done\n");

	if(state->window == NULL)
	{
		printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
#if !__EMSCRIPTEN__
	printf("SDL_VERSION...\n");
	SDL_VERSION(&state->wmi.version);
	if(
		!SDL_GetWindowWMInfo(
			state->window,
			&state->wmi  
		)
	)
	{
		printf("SDL_Error %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	printf("done\n");
	bgfx_render_frame(-1);
#endif


	bgfx_platform_data_t pd;
	memset(&pd, 0, sizeof(bgfx_platform_data_t));

#if !__EMSCRIPTEN__
	// x11
	pd.ndt = state->wmi.info.x11.display;
	pd.nwh = (void*)(uintptr_t)state->wmi.info.x11.window;
#else
	// web
	pd.nwh = (void*)"#canvas";
#endif

	bgfx_init_t init = {0};
	bgfx_init_ctor(&init);
	init.type = BGFX_RENDERER_TYPE_COUNT; // auto determine renderer
	//init.type = BGFX_RENDERER_TYPE_OPENGL; // force opengl renderer
	init.resolution.width = state->screen_width;
	init.resolution.height = state->screen_height;
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
	bgfx_set_view_rect(0, 0, 0, state->screen_width, state->screen_height);
	bgfx_vertex_layout_begin(&state->vertex_layout, bgfx_get_renderer_type());
	bgfx_vertex_layout_add(&state->vertex_layout, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT, false, false);
	bgfx_vertex_layout_add(&state->vertex_layout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_UINT8, true, false);
	bgfx_vertex_layout_end(&state->vertex_layout);

	state->vertex_buffer_handle = bgfx_create_dynamic_vertex_buffer(RODEO__MAX_VERTEX_SIZE, &state->vertex_layout, BGFX_BUFFER_NONE);

	state->index_buffer_handle = bgfx_create_dynamic_index_buffer((RODEO__MAX_VERTEX_SIZE / 4) * 6, BGFX_BUFFER_NONE);

	// load shaders
	const char* shader_path = "???";
	switch(bgfx_get_renderer_type()) {
        case BGFX_RENDERER_TYPE_NOOP:
			printf("Noop renderer error");
			exit(EXIT_FAILURE);
        case BGFX_RENDERER_TYPE_OPENGLES:
			shader_path = "shaders/100_es/"; 
			break;
        case BGFX_RENDERER_TYPE_VULKAN:
			shader_path = "shaders/spirv/";
			break;
		default:
			printf("No shaders for selected renderer. Exiting...");
			exit(EXIT_FAILURE);
    }
	const char* vertex_shader_filename = "simple.vertex.bin";
	const char* fragment_shader_filename = "simple.fragment.bin";
    size_t shader_length = strlen(shader_path);
    size_t fragment_length = strlen(fragment_shader_filename);
    size_t vertex_length = strlen(vertex_shader_filename);
    char *fragment_path = (char *)malloc(shader_length + fragment_length);
    char *vertex_path = (char *)malloc(shader_length + vertex_length);
    memcpy(fragment_path, shader_path, shader_length);
    memcpy(&fragment_path[shader_length], fragment_shader_filename, fragment_length);
    memcpy(vertex_path, shader_path, shader_length);
    memcpy(&vertex_path[shader_length], vertex_shader_filename, vertex_length);

	fragment_path[shader_length + fragment_length] = 0;
	vertex_path[shader_length + vertex_length] = 0;

	state->vertex_shader = _Rodeo__load_shader(vertex_path);
	state->fragment_shader = _Rodeo__load_shader(fragment_path);
	state->program_shader = bgfx_create_program(
		state->vertex_shader,
		state->fragment_shader,
		true
	);
}

void
Rodeo__\
deinit_window(Rodeo__data_p state)
{
	if(!state)
	{
		Rodeo__error_exit(
			RODEO__ERROR__UNINITIALIZED_STATE,
			__FUNCTION__,
			__LINE__,
			RODEO__EMPTY_ERROR_MESSAGE  
		);
	}
	bgfx_destroy_dynamic_index_buffer(state->index_buffer_handle);
	bgfx_destroy_dynamic_vertex_buffer(state->vertex_buffer_handle);
	bgfx_destroy_program(state->program_shader);
	bgfx_shutdown();
	SDL_DestroyWindow(state->window);
}

void
Rodeo__\
quit()
{
	SDL_Quit();
}

void
Rodeo__\
begin(Rodeo__data_p state)
{
	if(!state)
	{
		Rodeo__error_exit(
			RODEO__ERROR__UNINITIALIZED_STATE,
			__FUNCTION__,
			__LINE__,
			RODEO__EMPTY_ERROR_MESSAGE  
		);
	}
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
		state->screen_width,
		state->screen_height,
		0,
		// near
		-0.1f,
		// far
		100.0f,
		proj
	);
	bgfx_set_view_transform(0, view, proj);
	bgfx_set_view_rect(0, 0, 0, state->screen_width, state->screen_height);
	bgfx_touch(0);
}

void
Rodeo__\
end(Rodeo__data_p state)
{
	if(!state)
	{
		Rodeo__error_exit(
			RODEO__ERROR__UNINITIALIZED_STATE,
			__FUNCTION__,
			__LINE__,
			RODEO__EMPTY_ERROR_MESSAGE  
		);
	}
	Rodeo__flush_batch(state);

	bgfx_frame(false);

	while(SDL_PollEvent(&state->sdl_event))
	{
		if(state->sdl_event.type == SDL_QUIT)
		{
			state->quit = true;
		}
	}
}

void
Rodeo__\
execute_main_loop(
	Rodeo__data_p state,
	Rodeo__main_loop_p main_loop_function
)
{
#if __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop_function, 0, 1);
#else
	while(!Rodeo__should_quit(state))
	{
		main_loop_function();
	}
#endif
}

bool
Rodeo__\
should_quit(Rodeo__data_p state)
{
	return state->quit;
}

void
Rodeo__\
set_quit(Rodeo__data_p state, bool quit)
{
	state->quit = quit;
}

void
Rodeo__\
draw_debug_text(u_int16_t x, u_int16_t y, const char *format, ...)
{
	va_list argList;
	va_start(argList, format);
	bgfx_dbg_text_vprintf(x, y, 0x65, format, argList);
	va_end(argList);
}

const char *
Rodeo__\
get_renderer_name_as_string()
{
	return bgfx_get_renderer_name(bgfx_get_renderer_type());
}

void
Rodeo__\
flush_batch(Rodeo__data_p state)
{
	if(state->vertex_size > 0)
	{
		// upload remaining batched vertices
		bgfx_set_dynamic_vertex_buffer(0, state->vertex_buffer_handle, 0, state->vertex_size);
		const bgfx_memory_t* vbm = bgfx_copy(state->batched_vertices, sizeof(Rodeo__position_color_vertex_t) * state->vertex_size);
		bgfx_update_dynamic_vertex_buffer(state->vertex_buffer_handle,  0, vbm);

		// upload remaining batched indices
		bgfx_set_dynamic_index_buffer(state->index_buffer_handle, 0, state->index_size);
		const bgfx_memory_t* ibm = bgfx_copy(state->batched_indices, sizeof(uint16_t) * state->index_size);
		bgfx_update_dynamic_index_buffer(state->index_buffer_handle, 0, ibm);

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
		bgfx_submit(0, state->program_shader, 0, BGFX_DISCARD_ALL);

		// reset arrays
		state->vertex_size = 0;
		state->index_size = 0;
		state->index_count = 0;
	}
}

void
Rodeo__\
draw_rectangle(
	Rodeo__data_p state,
	u_int16_t x,
	u_int16_t y,
	u_int16_t width,
	u_int16_t height,
	Rodeo__color_rgba_t color
)
{
	const uint32_t abgr = Rodeo__Math__color_rgba_to_uint32(color);
	if(state->vertex_size < RODEO__MAX_VERTEX_SIZE)
	{
		state->batched_vertices[state->vertex_size] =
			(Rodeo__position_color_vertex_t)
			{
				(float)width + (float)x, (float)height + (float)y, 0.0f, abgr
			};
		state->vertex_size += 1;
		state->batched_vertices[state->vertex_size] =
			(Rodeo__position_color_vertex_t)
			{
				(float)width + (float)x, (float)y, 0.0f, abgr
			};
		state->vertex_size += 1;
		state->batched_vertices[state->vertex_size] =
			(Rodeo__position_color_vertex_t)
			{
				(float)x, (float)y, 0.0f, abgr
			};
		state->vertex_size += 1;
		state->batched_vertices[state->vertex_size] =
			(Rodeo__position_color_vertex_t)
			{
				(float)x, (float)height + (float)y, 0.0f, abgr
			};
		state->vertex_size += 1;

		int indices[] =
		{
			0, 1, 3,
			1, 2, 3
			//2, 1, 0,
			//2, 3, 1
		};
		state->batched_indices[state->index_size] = state->index_count + indices[0];
		state->index_size += 1;
		state->batched_indices[state->index_size] = state->index_count + indices[1];
		state->index_size += 1;
		state->batched_indices[state->index_size] = state->index_count + indices[2];
		state->index_size += 1;
		state->batched_indices[state->index_size] = state->index_count + indices[3];
		state->index_size += 1;
		state->batched_indices[state->index_size] = state->index_count + indices[4];
		state->index_size += 1;
		state->batched_indices[state->index_size] = state->index_count + indices[5];
		state->index_size += 1;
		state->index_count += 4;
	}

	if(state->vertex_size >= RODEO__MAX_VERTEX_SIZE)
	{
		Rodeo__flush_batch(state);
	}
}

bgfx_shader_handle_t
_Rodeo__\
load_shader(const char* path)
{
	bgfx_shader_handle_t invalid = BGFX_INVALID_HANDLE;

	FILE *file = fopen(path, "rb");

	if(!file)
	{
		printf("Error: shader file \"%s\" not found\n", path);
		return invalid;
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx_memory_t *mem = bgfx_alloc(file_size + 1);
	fread(mem->data, 1, file_size, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	bgfx_shader_handle_t shader = bgfx_create_shader(mem);
	printf("Shader loaded as idx: %d\n", shader.idx);

	return shader;
}

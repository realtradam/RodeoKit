
// -- internal --
// public
#include "rodeo/input_t.h"
#include "rodeo/input.h"
#include "irodeo_input.h"

// -- external --
#include "SDL2/SDL.h"

static irodeo_input_state_t state = {0};

bool
rodeo_input_events_poll(void)
{
	SDL_Event event = {0};
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				{
					return true;
				}
				break;
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				{
					c_foreach(i, cset_input_scene, state.active_scenes)
					{
						const cmap_input_scancode_scene_value *value = cmap_input_scancode_scene_get(
								&((*i.ref)->scancode),
								(rodeo_input_scancode_t)event.key.keysym.scancode
						);
						if(value == NULL)
						{
							continue;
						}
						else
						{
							rodeo_input_any_state_t key_state = {
								.binary_state = event.key.state,
								.type = rodeo_input_type_Binary
							};
							c_foreach(
								j,
								cvec_input_callback_functions,
								value->second
							)
							{
								(**j.ref)(key_state);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				{
					//event.button.button // which sdl mouse button it was
					//event.button.state // if thue button was clicked or released 
					c_foreach(i, cset_input_scene, state.active_scenes)
					{
						const cmap_input_mouse_scene_value *value = cmap_input_mouse_scene_get(
								&((*i.ref)->mouse),
								(rodeo_input_mouse_t)event.button.button
						);
						if(value == NULL)
						{
							continue;
						}
						else
						{
							rodeo_input_any_state_t key_state = {
								.binary_state = event.button.state,
								.type = rodeo_input_type_Binary
							};
							c_foreach(
								j,
								cvec_input_callback_functions,
								value->second
							)
							{
								(**j.ref)(key_state);
							}
						}
					}
				}
				break;
		}
	}
	return false;
}

void
rodeo_input_scene_activate(
	rodeo_input_scene_t *scene
)
{
	cset_input_scene_insert(&state.active_scenes, scene);
}

void
rodeo_input_scene_deactivate(
	rodeo_input_scene_t *scene
)
{
	cset_input_scene_erase(&state.active_scenes, scene);
}

void
rodeo_input_scene_register_callback(
	rodeo_input_callback_function func,
	rodeo_input_scene_t *scene,
	rodeo_input_register_type_t type
)
{
	switch (type.type)
	{
		case rodeo_input_type_Binary:
			switch (type.binary_type) {
				case rodeo_input_binary_Scancode:
					{
						if(!cmap_input_scancode_scene_contains(&scene->scancode, type.scancode))
						{
							cmap_input_scancode_scene_insert(&scene->scancode, type.scancode, cvec_input_callback_functions_init());
						}
						cvec_input_callback_functions* callbacks = cmap_input_scancode_scene_at_mut(&scene->scancode, type.scancode);
						cvec_input_callback_functions_push(callbacks, func);
					}
					break;

				case rodeo_input_binary_Mouse:
					{
						if(!cmap_input_mouse_scene_contains(&scene->mouse, type.mouse))
						{
							cmap_input_mouse_scene_insert(&scene->mouse, type.mouse, cvec_input_callback_functions_init());
						}
						cvec_input_callback_functions* callbacks = cmap_input_mouse_scene_at_mut(&scene->mouse, type.mouse);
						cvec_input_callback_functions_push(callbacks, func);
					}
					break;

				case rodeo_input_binary_Invalid:
					// TODO make it a log
					break;
			}
			break;
		case rodeo_input_type_Invalid:
			// TODO make it log
			break;
	}
}

void
rodeo_input_scene_unregister_callback(
	rodeo_input_callback_function func,
	rodeo_input_scene_t *scene,
	rodeo_input_register_type_t type
)
{

}

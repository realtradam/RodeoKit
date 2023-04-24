
// -- internal --
// public
#include "rodeo/input.h"
#include "irodeo_input_t.h"
#include "rodeo/log.h"

// -- external --
#include "SDL2/SDL.h"

static irodeo_input_state_t istate = {0};

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
			// - Binary -
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				{
					c_foreach(i, cset_input_scene, istate.active_scenes)
					{
						rodeo_input_scene_t *scene = *i.ref;
						c_foreach(j, cset_input_commands, scene->commands)
						{
							rodeo_input_command_t *command = *j.ref;
							const cset_input_binary_scancodes_value *value = cset_input_binary_scancodes_get(
									&command->binary.scancodes,
									(rodeo_input_binary_scancode_t)event.key.keysym.scancode
							);

							if(value == NULL)
							{
								continue;
							}
							else
							{
								rodeo_input_any_state_t key_state = {
									.data.binary_state = event.key.state,
									.input_type = rodeo_input_type_Binary
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(key_state);
								}
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				{
					c_foreach(i, cset_input_scene, istate.active_scenes)
					{
						rodeo_input_scene_t *scene = *i.ref;
						c_foreach(j, cset_input_commands, scene->commands)
						{
							rodeo_input_command_t *command = *j.ref;
							const cset_input_binary_mouseButtons_value *value = cset_input_binary_mouseButtons_get(
									&command->binary.mouse_buttons,
									(rodeo_input_binary_mouseButton_t)event.button.button

							);

							if(value == NULL)
							{
								continue;
							}
							else
							{
								rodeo_input_any_state_t input_state = {
									.data.binary_state = event.button.state,
									.input_type = rodeo_input_type_Binary
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(input_state);
								}
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
rodeo_input_command_register_callback(
	rodeo_input_command_t *command,
	rodeo_input_callback_function func
)
{
	const cset_input_callback_functions_value *callback = cset_input_callback_functions_get(&(command->callbacks), func);
	if(callback == NULL)
	{
		cset_input_callback_functions_insert(&(command->callbacks), func);
		return;
	}
	else
	{
		rodeo_log(
			rodeo_logLevel_warning,
			"Input already registered"
		);
		return;
	}
}

void
rodeo_input_command_unregister_callback(
	rodeo_input_command_t *command,
	rodeo_input_callback_function func
)
{
	cset_input_callback_functions_value *callback = 
		cset_input_callback_functions_get_mut(&(command->callbacks), func);
	if(callback != NULL)
	{
		cset_input_callback_functions_erase_entry(&(command->callbacks), callback);
		return;
	}
	else
	{
		rodeo_log(
			rodeo_logLevel_warning,
			"Attempted to remove callback but it is not registered"
		);
		return;
	}
}

rodeo_input_scene_t*
rodeo_input_scene_create(void)
{
	rodeo_input_scene_t *result = malloc(sizeof(rodeo_input_scene_t));
	*result = (rodeo_input_scene_t){0};
	return result;
}

void
rodeo_input_scene_destroy(rodeo_input_scene_t *scene)
{
	rodeo_input_scene_deactivate(scene);
	cset_input_commands_drop(&scene->commands);
	free(scene);
}

rodeo_input_command_t*
rodeo_input_command_create(uint32_t input_type)
{
	rodeo_input_command_t *result = malloc(sizeof(rodeo_input_command_t));
	*result = (rodeo_input_command_t)
	{
		.valid_types = input_type
	};
	return result;
}

void
rodeo_input_command_destroy(rodeo_input_command_t *command)
{
	cset_input_binary_scancodes_drop(&command->binary.scancodes);
	cset_input_binary_mouseButtons_drop(&command->binary.mouse_buttons);
	cset_input_callback_functions_drop(&command->callbacks);
	free(command);
}

bool
rodeo_input_command_register_binary_scancode(
	rodeo_input_command_t *input_command,
	rodeo_input_binary_scancode_t scancode
)
{
	if((rodeo_input_type_Binary & input_command->valid_types) == 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Attempting to register input type which is invalid for this input command, failed to do so"
		);
		return false;
	}
	else
	{
		cset_input_binary_scancodes_insert(
			&input_command->binary.scancodes,
			scancode
		);
		return true;
	}
}

bool
rodeo_input_command_register_binary_mouseButton(
	rodeo_input_command_t *input_command,
	rodeo_input_binary_mouseButton_t mouse_button
)
{
	if((rodeo_input_type_Binary & input_command->valid_types) == 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Attempting to register input type which is invalid for this input command, failed to do so"
		);
		return false;
	}
	else
	{
		cset_input_binary_mouseButtons_insert(
			&input_command->binary.mouse_buttons,
			mouse_button
		);
		return true;
	}
}

void
rodeo_input_scene_register_command(
	rodeo_input_scene_t *scene,
	rodeo_input_command_t *command
)
{
	cset_input_commands_insert(
			&scene->commands,
			command
	);
}

void
rodeo_input_scene_unregister_command(
	rodeo_input_scene_t *scene,
	rodeo_input_command_t *command
)
{
	cset_input_commands_erase(
			&scene->commands,
			command
	);
}

void
rodeo_input_scene_activate(rodeo_input_scene_t *scene)
{
	cset_input_scene_insert(&istate.active_scenes, scene);
}

void
rodeo_input_scene_deactivate(rodeo_input_scene_t *scene)
{
	cset_input_scene_erase(&istate.active_scenes, scene);
}

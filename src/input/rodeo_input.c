
// -- internal --
// public
#include "rodeo/input.h"
#include "irodeo_input_t.h"
#include "rodeo/log.h"

// -- external --
#include "SDL.h"

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
								rodeo_input_any_state_t input_state = {
									.data.binary_state = event.key.state,
									.type = rodeo_input_type_Binary
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
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
									.type = rodeo_input_type_Binary
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
								}
							}
						}
					}
				}
				break;
			case SDL_MOUSEMOTION:
				{
					c_foreach(i, cset_input_scene, istate.active_scenes)
					{
						rodeo_input_scene_t *scene = *i.ref;
						c_foreach(j, cset_input_commands, scene->commands)
						{
							rodeo_input_command_t *command = *j.ref;
							const cset_input_positional_mouse_value *x_value = cset_input_positional_mouse_get(
									&command->positional.mouse_axes,
									rodeo_input_positional_mouse_X
								);
							const cset_input_positional_mouse_value *y_value = cset_input_positional_mouse_get(
									&command->positional.mouse_axes,
									rodeo_input_positional_mouse_Y
								);
							const cset_input_unboundedRange_mouse_value *rel_x_value =
								cset_input_unboundedRange_mouse_get(
									&command->unbounded_range.mouse_axes, 
									rodeo_input_unboundedRange_mouse_X
								);
							const cset_input_unboundedRange_mouse_value *rel_y_value =
								cset_input_unboundedRange_mouse_get(
									&command->unbounded_range.mouse_axes, 
									rodeo_input_unboundedRange_mouse_Y
								);

							if(x_value != NULL)
							{
								rodeo_input_any_state_t input_state = {
									.data.positional_state = event.motion.x,
									.type = rodeo_input_type_Positional
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
								}
							}

							if(y_value != NULL)
							{
								rodeo_input_any_state_t input_state = {
									.data.positional_state = event.motion.y,
									.type = rodeo_input_type_Positional
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
								}
							}
							if(rel_x_value != NULL)
							{
								rodeo_input_any_state_t input_state = {
									.data.unbounded_range_state = (float)event.motion.xrel,
									.type = rodeo_input_type_UnboundedRange
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
								}
							}

							if(rel_y_value != NULL)
							{
								rodeo_input_any_state_t input_state = {
									.data.unbounded_range_state = (float)event.motion.yrel,
									.type = rodeo_input_type_UnboundedRange
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
								}
							}
						}
					}
				}
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				{
					c_foreach(i, cset_input_scene, istate.active_scenes)
					{
						rodeo_input_scene_t *scene = *i.ref;
						c_foreach(j, cset_input_commands, scene->commands)
						{
							rodeo_input_command_t *command = *j.ref;
							const cset_input_binary_controllerButton_value *value = cset_input_binary_controllerButton_get(
									&command->binary.controller_buttons,
									(rodeo_input_binary_controllerButton_t)event.cbutton.button
							);

							if(value == NULL)
							{
								continue;
							}
							else
							{
								rodeo_input_any_state_t input_state = {
									.data.binary_state = event.cbutton.state,
									.type = rodeo_input_type_Binary
								};
								c_foreach(
									k,
									cset_input_callback_functions,
									command->callbacks
								)
								{
									(**k.ref)(&input_state, NULL);
								}
							}
						}
					}
				}
				break;
			case SDL_CONTROLLERAXISMOTION:
				{
					c_foreach(i, cset_input_scene, istate.active_scenes)
					{
						rodeo_input_scene_t *scene = *i.ref;
						c_foreach(j, cset_input_commands, scene->commands)
						{
							rodeo_input_command_t *command = *j.ref;
							if(cset_input_boundedRange_controllerAxis_contains(&command->bounded_range.controller_axes, event.caxis.axis))
							{
									rodeo_input_any_state_t input_state = {
										.data.bounded_range_state =
											(float)event.caxis.value/(float)UINT16_MAX,
										.type = rodeo_input_type_BoundedRange
									};
									c_foreach(
										k,
										cset_input_callback_functions,
										command->callbacks
									)
									{
										(**k.ref)(&input_state, NULL);
									}
								}
							}

						}
				}
				break;
			case SDL_CONTROLLERDEVICEADDED:
				{
					irodeo_input_controller_register(event.cdevice.which);
				}
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				{
					irodeo_input_controller_unregister(event.cdevice.which);
				}
				break;
			case SDL_CONTROLLERDEVICEREMAPPED:
				{
					rodeo_log(
						rodeo_logLevel_warning,
						"SDL Controller device was remapped"
					);
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
rodeo_input_command_create(uint32_t input_types)
{
	rodeo_input_command_t *result = malloc(sizeof(rodeo_input_command_t));
	*result = (rodeo_input_command_t)
	{
		.valid_types = input_types
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
rodeo_input_command_register_binary_controllerButton(
	rodeo_input_command_t *input_command,
	rodeo_input_binary_controllerButton_t button
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
		cset_input_binary_controllerButton_insert(
			&input_command->binary.controller_buttons,
			button
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

bool
rodeo_input_command_register_positional_mouse(
	rodeo_input_command_t *input_command,
	rodeo_input_positional_mouse_t mouse_axis
)
{
	if((rodeo_input_type_Positional & input_command->valid_types) == 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Attempting to register input type which is invalid for this input command, failed to do so"
		);
		return false;
	}
	else
	{
		cset_input_positional_mouse_insert(
			&input_command->positional.mouse_axes,
			mouse_axis
		);
		return true;
	}
}

bool
rodeo_input_command_register_boundedRange_controllerAxis(
	rodeo_input_command_t *input_command,
	rodeo_input_boundedRange_controllerAxis_t controller_axis
)
{
	if((rodeo_input_type_BoundedRange & input_command->valid_types) == 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Attempting to register input type which is invalid for this input command, failed to do so"
		);
		return false;
	}
	else
	{
		cset_input_boundedRange_controllerAxis_insert(
			&input_command->bounded_range.controller_axes,
			controller_axis
		);
		return true;
	}
}

bool
rodeo_input_command_register_unboundedRange_mouse(
	rodeo_input_command_t *input_command,
	rodeo_input_unboundedRange_mouse_t mouse_axis
)
{
	if((rodeo_input_type_UnboundedRange & input_command->valid_types) == 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Attempting to register input type which is invalid for this input command, failed to do so"
		);
		return false;
	}
	else
	{
		cset_input_unboundedRange_mouse_insert(
			&input_command->unbounded_range.mouse_axes,
			mouse_axis
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

#define i_key int32_t
#define i_val SDL_GameController*
#define i_tag SDL_GameController
#include "stc/cmap.h"

static cmap_SDL_GameController icontrollers = {0};

void
irodeo_input_controller_register(int32_t id)
{
	if(SDL_IsGameController(id))
	{
		SDL_GameController *controller = SDL_GameControllerOpen(id);
		cmap_SDL_GameController_insert(&icontrollers, id, controller);
	}
	else
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Invalid controller id, cannot register"
		);
	}
}

void
irodeo_input_controller_unregister(int32_t id)
{
	SDL_GameController *controller = cmap_SDL_GameController_get(&icontrollers, id)->second;
	SDL_GameControllerClose(controller);
	cmap_SDL_GameController_erase(&icontrollers, id);
}

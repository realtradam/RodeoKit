
// -- internal --
// public
#include "rodeo/input_t.h"

bool
rodeo_input_events_poll(void);

void
rodeo_input_command_register_callback(
	rodeo_input_command_t *command,
	rodeo_input_callback_function func
);

void
rodeo_input_command_unregister_callback(
	rodeo_input_command_t *command,
	rodeo_input_callback_function func
);

rodeo_input_scene_t*
rodeo_input_scene_create(void);

void
rodeo_input_scene_destroy(rodeo_input_scene_t *scene);

rodeo_input_command_t*
rodeo_input_command_create(uint32_t input_types);

// make sure to unregister from all scenes before destroying
void
rodeo_input_command_destroy(rodeo_input_command_t *command);

// returns false if attempting to register
// input type that has been set as valid
bool
rodeo_input_command_register_binary_scancode(
	rodeo_input_command_t *input_command,
	rodeo_input_binary_scancode_t scancode
);

bool
rodeo_input_command_register_binary_mouseButton(
	rodeo_input_command_t *input_command,
	rodeo_input_binary_mouseButton_t mouse_button
);

bool
rodeo_input_command_register_positional_mouse(
	rodeo_input_command_t *input_command,
	rodeo_input_positional_mouse_t mouse_axis
);

bool
rodeo_input_command_register_boundedRange_controllerAxis(
	rodeo_input_command_t *input_command,
	rodeo_input_boundedRange_controllerAxis_t controller_axis
);

bool
rodeo_input_command_register_unboundedRange_mouse(
	rodeo_input_command_t *input_command,
	rodeo_input_unboundedRange_mouse_t mouse_axis
);

// alternative proposed "general" registration methods
//rodeo_input_command_register_binary(cmd, rodeo_input_binary_Scancode, rodeo_input_binary_scancode_Q );
//rodeo_input_command_register_any(cmd, rodeo_input_type_Binary, rodeo_input_binary_Scancode, rodeo_input_binary_scancode_Q );
	
void
rodeo_input_scene_register_command(
	rodeo_input_scene_t *scene,
	rodeo_input_command_t *command
);

void
rodeo_input_scene_unregister_command(
	rodeo_input_scene_t *scene,
	rodeo_input_command_t *command
);

void
rodeo_input_scene_activate(
	rodeo_input_scene_t *scene
);

void
rodeo_input_scene_deactivate(
	rodeo_input_scene_t *scene
);

void
irodeo_input_controller_register(int32_t id);

void
irodeo_input_controller_unregister(int32_t id);

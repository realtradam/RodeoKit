
// -- internal --
// public
#include "rodeo/input_t.h"

bool
rodeo_input_events_poll(void);

void
rodeo_input_scene_activate(
	rodeo_input_scene_t *scene
);

void
rodeo_input_scene_deactivate(
	rodeo_input_scene_t *scene
);

void
rodeo_input_scene_register_callback(
	rodeo_input_callback_function func,
	rodeo_input_scene_t *scene,
	rodeo_input_register_type_t type
);

void
rodeo_input_scene_unregister_callback(
	rodeo_input_callback_function func,
	rodeo_input_scene_t *scene,
	rodeo_input_register_type_t type
);

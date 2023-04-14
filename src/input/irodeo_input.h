
// -- internal --
// public
#include "rodeo/input_t.h"

typedef rodeo_input_scene_t *rodeo_input_scene_p;
#define i_tag input_scene
#define i_key rodeo_input_scene_p
#include <stc/cset.h>

typedef
struct
{
	cset_input_scene active_scenes;
}
irodeo_input_state_t;

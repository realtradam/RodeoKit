#pragma once

// --- internal ---
// public
#include "rodeo/math_t.h"
#include "rodeo/math/vec2.h"
#include "rodeo/math/vec3.h"
#include "rodeo/math/mat4.h"

#define mrodeo_math_pi 3.1415927410125732421875f

float
rodeo_math_radians_to_turns(float radians);

float
rodeo_math_turns_to_radians(float turns);

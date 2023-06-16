
#pragma once

// -- internal --
// public
#include "rodeo/math/vec3_t.h"
// private
#include "math/irodeo_math.h"

rodeo_math_vec3_t
irodeo_math_cglmVec3_to_rodeoVec3(vec3s in);

vec3s
irodeo_math_rodeoVec3_to_cglmVec3(rodeo_math_vec3_t in);


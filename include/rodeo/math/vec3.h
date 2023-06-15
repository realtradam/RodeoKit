#pragma once

// -- internal --
// public
#include "rodeo/math/vec3_t.h"

rodeo_math_vec3_t
rodeo_math_vec3_zero(void);

rodeo_math_vec3_t
rodeo_math_vec3_one(void);

float
rodeo_math_vec3_dot(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

float
rodeo_math_vec3_cross(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

rodeo_math_vec3_t
rodeo_math_vec3_add(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

rodeo_math_vec3_t
rodeo_math_vec3_subtract(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

rodeo_math_vec3_t
rodeo_math_vec3_multiply(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

rodeo_math_vec3_t
rodeo_math_vec3_scale(rodeo_math_vec3_t a, float b);

rodeo_math_vec3_t
rodeo_math_vec3_divide(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

rodeo_math_vec3_t
rodeo_math_vec3_negate(rodeo_math_vec3_t a);

rodeo_math_vec3_t
rodeo_math_vec3_normalize(rodeo_math_vec3_t a);

rodeo_math_vec3_t
rodeo_math_vec3_rotate(rodeo_math_vec3_t a, float turns, rodeo_math_vec3_t axis);

float
rodeo_math_vec3_distance(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

float
rodeo_math_vec3_distanceSq(rodeo_math_vec3_t a, rodeo_math_vec3_t b);

rodeo_math_vec3_t
rodeo_math_vec3_clamp(rodeo_math_vec3_t a, float minimum, float maximum);

rodeo_math_vec3_t
rodeo_math_vec3_lerp(rodeo_math_vec3_t from, rodeo_math_vec3_t to, float t);

#pragma once

// -- internal --
// public
#include "rodeo/math/vec2_t.h"

rodeo_math_vec2_t
rodeo_math_vec2_zero(void);

rodeo_math_vec2_t
rodeo_math_vec2_one(void);

float
rodeo_math_vec2_dot(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

float
rodeo_math_vec2_cross(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

rodeo_math_vec2_t
rodeo_math_vec2_add(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

rodeo_math_vec2_t
rodeo_math_vec2_subtract(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

rodeo_math_vec2_t
rodeo_math_vec2_multiply(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

rodeo_math_vec2_t
rodeo_math_vec2_scale(rodeo_math_vec2_t a, float b);

rodeo_math_vec2_t
rodeo_math_vec2_divide(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

rodeo_math_vec2_t
rodeo_math_vec2_negate(rodeo_math_vec2_t a);

rodeo_math_vec2_t
rodeo_math_vec2_normalize(rodeo_math_vec2_t a);

rodeo_math_vec2_t
rodeo_math_vec2_rotate(rodeo_math_vec2_t a, float turns);

float
rodeo_math_vec2_distance(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

float
rodeo_math_vec2_distanceSq(rodeo_math_vec2_t a, rodeo_math_vec2_t b);

rodeo_math_vec2_t
rodeo_math_vec2_clamp(rodeo_math_vec2_t a, float minimum, float maximum);

rodeo_math_vec2_t
rodeo_math_vec2_lerp(rodeo_math_vec2_t from, rodeo_math_vec2_t to, float t);

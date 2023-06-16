#pragma once

// -- internal --
// public
#include "rodeo/math/mat4_t.h"
#include "rodeo/math.h"

rodeo_math_mat4_t
rodeo_math_mat4_identity(void);

rodeo_math_mat4_t
rodeo_math_mat4_zero(void);

rodeo_math_mat4_t
rodeo_math_mat4_transpose(rodeo_math_mat4_t m);

rodeo_math_mat4_t
rodeo_math_mat4_translate(rodeo_math_mat4_t m, rodeo_math_vec3_t v);

rodeo_math_mat4_t
rodeo_math_mat4_scale(rodeo_math_mat4_t m, rodeo_math_vec3_t v);

rodeo_math_mat4_t
rodeo_math_mat4_rotate(rodeo_math_mat4_t m, float turns, rodeo_math_vec3_t v);

rodeo_math_mat4_t
rodeo_math_mat4_multiply(rodeo_math_mat4_t a, rodeo_math_mat4_t b);

rodeo_math_mat4_t
rodeo_math_mat4_orthographic(
	float left,
	float right,
	float bottom,
	float top,
	float near,
	float far
);


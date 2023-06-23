
// -- internal --
// public
#include "rodeo/math.h"
#include "rodeo/math/vec2.h"
// private
#include "math/irodeo_math.h"
#include "math/irodeo_vec2.h"

rodeo_math_vec2_t
irodeo_math_cglmVec2_to_rodeoVec2(vec2s in)
{
	return (rodeo_math_vec2_t){
		.raw[0] = in.raw[0],
		.raw[1] = in.raw[1]
	};
}

vec2s
irodeo_math_rodeoVec2_to_cglmVec2(rodeo_math_vec2_t in)
{
	return (vec2s){
		.raw[0] = in.raw[0],
		.raw[1] = in.raw[1]
	};
}


rodeo_math_vec2_t
rodeo_math_vec2_zero(void)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(glms_vec2_zero());
}

rodeo_math_vec2_t
rodeo_math_vec2_one(void)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(glms_vec2_one());
}

float
rodeo_math_vec2_dot(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return glms_vec2_dot(
		irodeo_math_rodeoVec2_to_cglmVec2(a),
		irodeo_math_rodeoVec2_to_cglmVec2(b)
	);
}

float
rodeo_math_vec2_cross(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return glms_vec2_cross(
		irodeo_math_rodeoVec2_to_cglmVec2(a),
		irodeo_math_rodeoVec2_to_cglmVec2(b)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_add(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_add(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			irodeo_math_rodeoVec2_to_cglmVec2(b)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_subtract(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_sub(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			irodeo_math_rodeoVec2_to_cglmVec2(b)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_multiply(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_mul(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			irodeo_math_rodeoVec2_to_cglmVec2(b)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_scale(rodeo_math_vec2_t a, float b)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_scale(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			b
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_divide(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_div(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			irodeo_math_rodeoVec2_to_cglmVec2(b)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_negate(rodeo_math_vec2_t a)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_negate(
			irodeo_math_rodeoVec2_to_cglmVec2(a)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_normalize(rodeo_math_vec2_t a)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_normalize(
			irodeo_math_rodeoVec2_to_cglmVec2(a)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_rotate(rodeo_math_vec2_t a, float turns)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_rotate(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			rodeo_math_radians_to_turns(turns)
		)
	);
}

float
rodeo_math_vec2_distance(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return (
		glms_vec2_distance(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			irodeo_math_rodeoVec2_to_cglmVec2(b)
		)
	);
}

float
rodeo_math_vec2_distanceSq(rodeo_math_vec2_t a, rodeo_math_vec2_t b)
{
	return (
		glms_vec2_distance2(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			irodeo_math_rodeoVec2_to_cglmVec2(b)
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_clamp(rodeo_math_vec2_t a, float minimum, float maximum)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_clamp(
			irodeo_math_rodeoVec2_to_cglmVec2(a),
			minimum,
			maximum
		)
	);
}

rodeo_math_vec2_t
rodeo_math_vec2_lerp(rodeo_math_vec2_t from, rodeo_math_vec2_t to, float t)
{
	return irodeo_math_cglmVec2_to_rodeoVec2(
		glms_vec2_lerp(
			irodeo_math_rodeoVec2_to_cglmVec2(from),
			irodeo_math_rodeoVec2_to_cglmVec2(to),
			t
		)
	);
}

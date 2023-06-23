
// -- internal --
// public
#include "rodeo/math.h"
#include "rodeo/math/vec3.h"
// private
#include "math/irodeo_math.h"
#include "math/irodeo_vec3.h"

rodeo_math_vec3_t
irodeo_math_cglmVec3_to_rodeoVec3(vec3s in)
{
	return (rodeo_math_vec3_t){
		.raw[0] = in.raw[0],
		.raw[1] = in.raw[1],
		.raw[2] = in.raw[2]
	};
}

vec3s
irodeo_math_rodeoVec3_to_cglmVec3(rodeo_math_vec3_t in)
{
	return (vec3s){
		.raw[0] = in.raw[0],
		.raw[1] = in.raw[1],
		.raw[2] = in.raw[2], 
	};
}

rodeo_math_vec3_t
rodeo_math_vec3_zero(void)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(glms_vec3_zero());
}

rodeo_math_vec3_t
rodeo_math_vec3_one(void)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(glms_vec3_one());
}

float
rodeo_math_vec3_dot(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return glms_vec3_dot(
		irodeo_math_rodeoVec3_to_cglmVec3(a),
		irodeo_math_rodeoVec3_to_cglmVec3(b)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_cross(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_cross(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_add(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_add(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_subtract(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_sub(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_multiply(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_mul(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_scale(rodeo_math_vec3_t a, float b)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_scale(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			b
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_divide(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_div(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_negate(rodeo_math_vec3_t a)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_negate(
			irodeo_math_rodeoVec3_to_cglmVec3(a)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_normalize(rodeo_math_vec3_t a)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_normalize(
			irodeo_math_rodeoVec3_to_cglmVec3(a)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_rotate(rodeo_math_vec3_t a, float turns, rodeo_math_vec3_t axis)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_rotate(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			rodeo_math_radians_to_turns(turns),
			irodeo_math_rodeoVec3_to_cglmVec3(axis)
		)
	);
}

float
rodeo_math_vec3_distance(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return (
		glms_vec3_distance(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

float
rodeo_math_vec3_distanceSq(rodeo_math_vec3_t a, rodeo_math_vec3_t b)
{
	return (
		glms_vec3_distance2(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			irodeo_math_rodeoVec3_to_cglmVec3(b)
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_clamp(rodeo_math_vec3_t a, float minimum, float maximum)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_clamp(
			irodeo_math_rodeoVec3_to_cglmVec3(a),
			minimum,
			maximum
		)
	);
}

rodeo_math_vec3_t
rodeo_math_vec3_lerp(rodeo_math_vec3_t from, rodeo_math_vec3_t to, float t)
{
	return irodeo_math_cglmVec3_to_rodeoVec3(
		glms_vec3_lerp(
			irodeo_math_rodeoVec3_to_cglmVec3(from),
			irodeo_math_rodeoVec3_to_cglmVec3(to),
			t
		)
	);
}

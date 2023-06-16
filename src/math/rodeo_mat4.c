
// -- internal --
// public
#include "rodeo/math.h"
#include "rodeo/log.h"
// private
#include "math/irodeo_math.h"

static inline
rodeo_math_mat4_t
irodeo_math_cglmMat4_to_rodeoMat4(mat4s in)
{
	return (rodeo_math_mat4_t){
		.val = {
			.m00 = in.raw[0][0], .m01 = in.raw[0][1], .m02 = in.raw[0][2], .m03 = in.raw[0][3],
			.m10 = in.raw[1][0], .m11 = in.raw[1][1], .m12 = in.raw[1][2], .m13 = in.raw[1][3],
			.m20 = in.raw[2][0], .m21 = in.raw[2][1], .m22 = in.raw[2][2], .m23 = in.raw[2][3],
			.m30 = in.raw[3][0], .m31 = in.raw[3][1], .m32 = in.raw[3][2], .m33 = in.raw[3][3]
		}
	};
}

static inline
mat4s
irodeo_math_rodeoMat4_to_cglmMat4(rodeo_math_mat4_t in)
{
	return (mat4s){
		.raw = {
			{
			in.val.m00, in.val.m01, in.val.m02, in.val.m03
			},
			{
			in.val.m10, in.val.m11, in.val.m12, in.val.m13
			},
			{
			in.val.m20, in.val.m21, in.val.m22, in.val.m23
			},
			{
			in.val.m30, in.val.m31, in.val.m32, in.val.m33
			},
		}
	};
}

void
irodeo_print_matrix(rodeo_math_mat4_t mat)
{
	rodeo_log(
		rodeo_logLevel_warning,
		"%.05f, %.05f, %.05f, %.05f",
		mat.raw[0][0],
		mat.raw[0][1],
		mat.raw[0][2],
		mat.raw[0][3]
	);
	rodeo_log(
		rodeo_logLevel_info,
		"%.05f, %.05f, %.05f, %.05f",
		mat.raw[1][0],
		mat.raw[1][1],
		mat.raw[1][2],
		mat.raw[1][3]
	);
	rodeo_log(
		rodeo_logLevel_info,
		"%.05f, %.05f, %.05f, %.05f",
		mat.raw[2][0],
		mat.raw[2][1],
		mat.raw[2][2],
		mat.raw[2][3]
	);
	rodeo_log(
		rodeo_logLevel_info,
		"%.05f, %.05f, %.05f, %.05f",
		mat.raw[3][0],
		mat.raw[3][1],
		mat.raw[3][2],
		mat.raw[3][3]
	);
}


rodeo_math_mat4_t
rodeo_math_mat4_identity(void)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(glms_mat4_identity());
}

rodeo_math_mat4_t
rodeo_math_mat4_zero(void)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(glms_mat4_zero());
}

rodeo_math_mat4_t
rodeo_math_mat4_transpose(rodeo_math_mat4_t m)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(
		glms_mat4_transpose(
			irodeo_math_rodeoMat4_to_cglmMat4(m)
		)
	);
}

rodeo_math_mat4_t
rodeo_math_mat4_translate(rodeo_math_mat4_t m, rodeo_math_vec3_t v)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(
			glms_translate(
				irodeo_math_rodeoMat4_to_cglmMat4(m),
				irodeo_math_rodeoVec3_to_cglmVec3(v)
			)
	);
}

rodeo_math_mat4_t
rodeo_math_mat4_scale(rodeo_math_mat4_t m, rodeo_math_vec3_t v)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(
			glms_scale(
				irodeo_math_rodeoMat4_to_cglmMat4(m),
				irodeo_math_rodeoVec3_to_cglmVec3(v)
			)
	);
}

rodeo_math_mat4_t
rodeo_math_mat4_rotate(rodeo_math_mat4_t m, float turns, rodeo_math_vec3_t v)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(
			glms_rotate(
				irodeo_math_rodeoMat4_to_cglmMat4(m),
				turns,
				irodeo_math_rodeoVec3_to_cglmVec3(v)
			)
	);
}

rodeo_math_mat4_t
rodeo_math_mat4_multiply(rodeo_math_mat4_t a, rodeo_math_mat4_t b)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(
			glms_mat4_mul(
				irodeo_math_rodeoMat4_to_cglmMat4(a),
				irodeo_math_rodeoMat4_to_cglmMat4(b)
			)
	);
}

rodeo_math_mat4_t
rodeo_math_mat4_orthographic(
	float left,
	float right,
	float bottom,
	float top,
	float near,
	float far
)
{
	return irodeo_math_cglmMat4_to_rodeoMat4(
			glms_ortho_rh_zo(
				left,
				right,
				bottom,
				top,
				near,
				far
			)
	);
}


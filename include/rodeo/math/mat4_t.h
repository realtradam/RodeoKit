#pragma once


typedef
struct
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
}
rodeo_math_mat4_val_t;

typedef
union
{
	rodeo_math_mat4_val_t val;
	float raw[4][4];
}
rodeo_math_mat4_t;

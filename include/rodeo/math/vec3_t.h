#pragma once

typedef
struct
{
	float x;
	float y;
	float z;
}
rodeo_math_vec3_val_t;

typedef
union
{
	rodeo_math_vec3_val_t val;
	float raw[3];
}
rodeo_math_vec3_t;

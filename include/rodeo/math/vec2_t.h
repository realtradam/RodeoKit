#pragma once

typedef
struct
{
	float x;
	float y;
}
rodeo_math_vec2_val_t;

typedef
union
{
	rodeo_math_vec2_val_t val;
	float raw[2];
}
rodeo_math_vec2_t;

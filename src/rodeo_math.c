
// -- internal --
// public
#include "rodeo.h"
// private
#include "rodeo_internal.h"

// -- system --
#include <stdint.h>
#include <math.h>

// -- external --
#include "SDL2/SDL.h"
#include "stc/crandom.h"
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
#include "cglm/cglm.h"

// rounds to nearest rather then truncation
rodeo_color_RGBA8_t
rodeo_color_RGBAFloat_to_RGBA8(const rodeo_color_RGBAFloat_t color)
{
	return (rodeo_color_RGBA8_t){
		.colors.red = (uint8_t)((color.colors.red * (float)UINT8_MAX) + 0.5),
		.colors.green = (uint8_t)((color.colors.green * (float)UINT8_MAX) + 0.5),
		.colors.blue = (uint8_t)((color.colors.blue * (float)UINT8_MAX) + 0.5),
		.colors.alpha = (uint8_t)((color.colors.alpha * (float)UINT8_MAX) + 0.5),
	};
}

rodeo_color_RGBAFloat_t
rodeo_color_RGBA8_to_RGBAFloat(const rodeo_color_RGBA8_t color)
{
	return (rodeo_color_RGBAFloat_t){
		.colors.red = (float)color.colors.red / 255.0f,
		.colors.green = (float)color.colors.green / 255.0f,
		.colors.blue = (float)color.colors.blue / 255.0f,
		.colors.alpha = (float)color.colors.alpha / 255.0f,
	};
}

void
rodeo_random_seed_set(uint64_t seed)
{
	irodeo_random_seed_set(stc64_new(seed));
}

double
rodeo_random_double_get(void)
{
	stc64_t *seed = irodeo_random_seed_get();
	return stc64_randf(seed);
}

uint64_t
rodeo_random_uint64_get(void)
{
	stc64_t *seed = irodeo_random_seed_get();
	return stc64_rand(seed);
}

// need to test this, might be wrong
/*
rodeo_vector2_t
rodeo_angle_to_vector2(float angle)
{
	rodeo_vector2_t result = { {1.0f, 0.0f} };
	glm_vec2_rotate(
			(float*)&(result.array),
			angle * 2.0f * (float)GLM_PI,
			(float*)&result.array
		);
	return result;
}
*/



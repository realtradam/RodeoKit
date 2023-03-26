
// -- internal --
// public
#include "rodeo.h"

// -- system --
#include <stdint.h>

// -- external --
#include "SDL2/SDL.h"

// rounds to nearest rather then truncation
rodeo_color_RGBA8_t
rodeo_color_RGBAFloat_to_RGBA8(const rodeo_color_RGBAFloat_t color)
{
	return (rodeo_color_RGBA8_t){
		.red = (uint8_t)((color.red * (float)UINT8_MAX) + 0.5),
		.green = (uint8_t)((color.green * (float)UINT8_MAX) + 0.5),
		.blue = (uint8_t)((color.blue * (float)UINT8_MAX) + 0.5),
		.alpha = (uint8_t)((color.alpha * (float)UINT8_MAX) + 0.5),
	};
}

rodeo_color_RGBAFloat_t
rodeo_color_RGBA8_to_RGBAFloat(const rodeo_color_RGBA8_t color)
{
	return (rodeo_color_RGBAFloat_t){
		.red = (float)color.red / 255.0f,
		.green = (float)color.green / 255.0f,
		.blue = (float)color.blue / 255.0f,
		.alpha = (float)color.alpha / 255.0f,
	};
}

double
rodeo_random_simple_float_get(void)
{
	return 0;
}

uint64_t
rodeo_random_simple_uint64_get(void)
{
	return 0;
}




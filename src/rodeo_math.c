
// public internal
#include "rodeo.h"

// system
#include <stdint.h>

// when casting from float to int(example):
// 20.50-21.00 rounds up to 21
// 20.00-20.49 rounds down to 20
rodeo_RGBA8_t
rodeo_RGBAFloat_to_RGBA8(const rodeo_RGBAFloat_t color)
{
	return (rodeo_RGBA8_t){
		.red = (uint8_t)((color.red * (float)UINT8_MAX) + 0.5),
		.green = (uint8_t)((color.green * (float)UINT8_MAX) + 0.5),
		.blue = (uint8_t)((color.blue * (float)UINT8_MAX) + 0.5),
		.alpha = (uint8_t)((color.alpha * (float)UINT8_MAX) + 0.5),
	};
}

rodeo_BGRA8_t
rodeo_RGBA8_to_BGRA8(const rodeo_RGBA8_t color)
{
	return (rodeo_BGRA8_t){
		.alpha = color.alpha,
		.blue = color.blue,
		.green = color.green,
		.red = color.red,
	};
}

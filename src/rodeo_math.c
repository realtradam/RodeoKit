#include "rodeo.h"
#include "rodeo_math.h"

uint32_t
Rodeo__\
Math__\
color_rgba_to_uint32(const struct Rodeo__color_rgba_t color)
{
	return
	  ((uint32_t)(uint8_t)(color.red   * 255))
	| ((uint32_t)(uint8_t)(color.green * 255)) << (8 * 1)
	| ((uint32_t)(uint8_t)(color.blue  * 255)) << (8 * 2)
	| ((uint32_t)(uint8_t)(color.alpha * 255)) << (8 * 3);
}

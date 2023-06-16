#pragma once

// -- system --
#include <inttypes.h>

typedef struct irodeo_math_rng_generator irodeo_math_rng_generator_t;

typedef
struct
{
	// note: a seed value of '0' is reserved for when using the
	// global seed is desired.
	uint64_t seed;
	irodeo_math_rng_generator_t *data;
}
rodeo_math_rng_generator_t;

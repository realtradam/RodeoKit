
// internal
// public
#include "rodeo/math/rng.h"
// private
#include "math/irodeo_rng_t.h"

// external
#include "stc/crand.h"
#include "SDL.h"

// system
#include <inttypes.h>

void
rodeo_math_rng_init(void)
{
	csrand(SDL_GetTicks64());
}

void
rodeo_math_rng_deinit(void)
{
	// no need to do anything
}

rodeo_math_rng_generator_t
rodeo_math_rng_generator_create(uint64_t seed)
{
	rodeo_math_rng_generator_t result = {
		.seed = seed,
		.data = malloc(sizeof(*(rodeo_math_rng_generator_t){0}.data))
	};
	result.data->crand = crand_init(seed);
	return result;
}

void
rodeo_math_rng_generator_destroy(rodeo_math_rng_generator_t generator)
{
	free(generator.data);
}

double
rodeo_math_rng_double_get(rodeo_math_rng_generator_t generator)
{
	if(generator.seed == 0)
	{
		return crandf();
	}
	else
	{
		return crand_f64(&generator.data->crand);
	}
}

float
rodeo_math_rng_float_get(rodeo_math_rng_generator_t generator)
{
	return (float)rodeo_math_rng_double_get(generator);
}

uint64_t
rodeo_math_rng_uint64_get(rodeo_math_rng_generator_t generator)
{
	if(generator.seed == 0)
	{
		return crand();
	}
	else
	{
		return crand_u64(&generator.data->crand);
	}
}

uint32_t
rodeo_math_rng_uint32_get(rodeo_math_rng_generator_t generator)
{
	return (uint32_t)rodeo_math_rng_uint64_get(generator);
}


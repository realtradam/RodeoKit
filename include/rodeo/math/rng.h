#pragma once

// -- internal --
#include "rodeo/math/rng_t.h"

// -- system --
#include <inttypes.h>

void
rodeo_math_rng_init(void);

void
rodeo_math_rng_deinit(void);

rodeo_math_rng_generator_t
rodeo_math_rng_generator_create(uint64_t seed);

void
rodeo_math_rng_generator_destroy(rodeo_math_rng_generator_t generator);

double
rodeo_math_rng_double_get(rodeo_math_rng_generator_t generator);

#define irodeo_math_rng_double_get_default() rodeo_math_rng_double_get((rodeo_math_rng_generator_t){0})

float
rodeo_math_rng_float_get(rodeo_math_rng_generator_t generator);

#define irodeo_math_rng_float_get_default() rodeo_math_rng_float_get((rodeo_math_rng_generator_t){0})

uint64_t
rodeo_math_rng_uint64_get(rodeo_math_rng_generator_t generator);

#define irodeo_math_rng_uint64_get_default() rodeo_math_rng_uint64_get((rodeo_math_rng_generator_t){0})

uint32_t
rodeo_math_rng_uint32_get(rodeo_math_rng_generator_t generator);

#define irodeo_math_rng_uint32_get_default() rodeo_math_rng_uint32_get((rodeo_math_rng_generator_t){0})

#define									\
mrodeo_math_rng_do(						\
)										\
	mrodeo_defer_do(					\
		rodeo_math_rng_init(),	\
		rodeo_math_rng_deinit()				\
	)


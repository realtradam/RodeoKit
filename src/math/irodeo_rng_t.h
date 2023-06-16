#pragma once

// -- internal --
// public
#include "rodeo/math/rng_t.h"
// private
#include "math/irodeo_rng_t.h"

// -- external --
#include "stc/crand.h"

typedef
struct
{
	rodeo_math_rng_generator_t global_generator;
}
irodeo_math_rng_state_t;

struct
irodeo_math_rng_generator
{
	crand_t crand;
};

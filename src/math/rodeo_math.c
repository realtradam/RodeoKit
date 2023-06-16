
// -- internal --
// public
#include "rodeo/math.h"

// -- system --
#include "math.h"

float
rodeo_math_radians_to_turns(float radians)
{
	return (radians / mrodeo_math_pi) / 2.0f;
}

float
rodeo_math_turns_to_radians(float turns)
{
	return turns * mrodeo_math_pi * 2.0f;
}


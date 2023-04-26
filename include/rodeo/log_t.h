#pragma once

// -- external --
#include "stc/cstr.h"

typedef
enum
{
	rodeo_logLevel_info,
	rodeo_logLevel_warning,
	rodeo_logLevel_error
}
rodeo_logLevel_t;

typedef
void
(*rodeo_log_function)(cstr text);

typedef 
union
{
	struct
	{
		float x;
		float y;
	}
	position;
	float array[2];
}
rodeo_vector2_t;

typedef 
union
{
	struct
	{
		float x;
		float y;
		float z;
	}
	position;
	float array[3];
}
rodeo_vector3_t;


// public internal
#include "rodeo_types.h"
#include "rodeo.h"

// external
#include "SDL2/SDL.h"

static rodeo_log_function logging_function = NULL;

void
rodeo_log(
	rodeo_logLevel_t loglevel,
	const char *format,
	...
)
{
	cstr formatted;
	mrodeo_vargs_do(format)
	{
		formatted = cstr_from_vfmt(format, vargs);
	}

	switch(loglevel)
	{
		case rodeo_logLevel_info:
			cstr_insert(
				&formatted,
				0,
				"[INFO]: "
			);
			break;
		case rodeo_logLevel_warning:
			cstr_insert(
				&formatted,
				0,
				"\033[33m[WARN]:\033[0m "
			);
			break;
		case rodeo_logLevel_error:
			cstr_insert(
				&formatted,
				0,
				"\033[31;1m[ERROR]:\033[0m "
			);
			break;
	}
	cstr_append(
		&formatted,
		"\n"
	);

	if(logging_function == NULL)
	{
		printf("%s", cstr_str(&formatted));
	}
	else
	{
		logging_function(formatted);
	}
}

void
rodeo_log_function_set(rodeo_log_function rodeo_log_func)
{
	logging_function = rodeo_log_func;
}


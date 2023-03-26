
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
	rodeo_string_t formatted;
	mrodeo_vargs_do(format)
	{
		formatted = rodeo_string_vargs_format(format, vargs);
	}

	switch(loglevel)
	{
		case rodeo_logLevel_info:
			rodeo_string_prepend(
				&formatted,
				rodeo_string_create("[INFO]: ")
			);
			break;
		case rodeo_logLevel_warning:
			rodeo_string_prepend(
				&formatted,
				rodeo_string_create("\033[33m[WARN]:\033[0m ")
			);
			break;
		case rodeo_logLevel_error:
			rodeo_string_prepend(
				&formatted,
				rodeo_string_create("\033[31;1m[ERROR]:\033[0m ")
			);
			break;
	}
	rodeo_string_append(
		&formatted,
		rodeo_string_create("\n")
	);

	if(logging_function == NULL)
	{
		printf("%s", rodeo_string_to_constcstr(&formatted));
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


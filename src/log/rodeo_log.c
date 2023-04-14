
// -- internal --
// public
#include "rodeo/log.h"
#include "rodeo/common.h"
// private
#include "log/irodeo_log.h"

static irodeo_log_state_t istate = {0};

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

	if(istate.logging_function == NULL)
	{
		printf("%s", cstr_str(&formatted));
	}
	else
	{
		istate.logging_function(formatted);
	}
}

void
rodeo_log_function_set(rodeo_log_function rodeo_log_func)
{
	istate.logging_function = rodeo_log_func;
}

rodeo_log_function
rodeo_log_function_get(void)
{
	return istate.logging_function;
}

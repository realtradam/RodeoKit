
// -- internal --
// public
#include "rodeo/log_t.h"

void
rodeo_log(
	rodeo_logLevel_t loglevel,
	const char *format,
	...
);

void
rodeo_log_function_set(
	rodeo_log_function rodeo_log_func
);

rodeo_log_function
rodeo_log_function_get(void);

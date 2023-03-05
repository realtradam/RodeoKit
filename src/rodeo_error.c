
// private internal
#include "private/rodeo_error.h"

// system
#include <stdlib.h>
#include <stdio.h>

void
Rodeo__\
error_exit(
	Rodeo__error error,
	const char *function,
	int line_number,
	const char *extra_info
)
{
	switch(error)
	{
		case RODEO__ERROR__UNREACHABLE_REACHED:
			printf("[ERROR] RODEO: \n\t(func: %s, line: %d)\n", function, line_number);
			printf("\tUnreachable code reached.\n");
			if(extra_info)
			{
				printf("\t%s\n", extra_info);
			}
			fflush(stdout);
			break;
		case RODEO__ERROR__UNINITIALIZED_STATE:
			printf("RODEO ERROR: \n\t(func: %s, line: %d)\n", function, line_number);
			printf("\tUninitialized State.\n");
			if(extra_info)
			{
				printf("\t%s\n", extra_info);
			}
			fflush(stdout);
			break;
		default:
			Rodeo__error_exit(
				RODEO__ERROR__UNREACHABLE_REACHED,
				__func__,
				__LINE__,
				"Unhandled error code."
			);
	}
	exit(EXIT_FAILURE);
}


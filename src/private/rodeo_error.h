
#define RODEO__EMPTY_ERROR_MESSAGE NULL

typedef
enum
{
	RODEO__ERROR__UNREACHABLE_REACHED,
	RODEO__ERROR__UNINITIALIZED_STATE
}
Rodeo__\
error;

void
Rodeo__\
error_exit(
	Rodeo__error error,
	const char *function,
	int line_number,
	const char *extra_info
);

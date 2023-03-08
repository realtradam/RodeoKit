
// internal
#include "rodeo.h"
#include "rodeo_types.h"

// external
#define i_implement
#include <stc/cstr.h>

typedef union cstr rodeo_string_t;

rodeo_string_p
rodeo_string_create(const char *c_string)
{
	cstr* result = calloc(1, sizeof(cstr));
	if(c_string != NULL)
	{
		*result = cstr_from(c_string);
	}
	return (rodeo_string_p)result;
}

void
rodeo_string_destroy(rodeo_string_p self)
{
	cstr_drop((cstr*)self);
	//free(string); // the above already calls free on the entire pointer
}

char*
rodeo_string_to_cstr(rodeo_string_p self)
{
	return cstr_data((cstr*)self);
}

const char*
rodeo_string_to_constcstr(rodeo_string_p self)
{
	return cstr_str((cstr*)self);
}

void
rodeo_string_insert(
	rodeo_string_p self,
	const rodeo_string_p insert,
	intptr_t position
)
{
	cstr_insert_s((cstr*)self, position, *(cstr*)insert);
}

void
rodeo_string_append(
	rodeo_string_p self,
	const rodeo_string_p append
)
{
	rodeo_string_insert(
		self,
		append,
		cstr_size((cstr*)self) - 1
	);
}

void
rodeo_string_prepend(
	rodeo_string_p self,
	const rodeo_string_p prepend
)
{
	rodeo_string_insert(
		self,
		prepend,
		0
	);
}

void
rodeo_string_clear(rodeo_string_p self)
{
	cstr_clear((cstr*)self);
}

void
rodeo_string_set(rodeo_string_p self, char* value)
{
	cstr_clear((cstr*)self);
	cstr *temp = (cstr*)self;
	*temp = cstr_from(value);
}


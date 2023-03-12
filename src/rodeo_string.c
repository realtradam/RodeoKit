
// internal
#include "rodeo.h"
#include "rodeo_types.h"

// external
#define i_implement
#include "stc/cstr.h"
#include "SDL2/SDL.h"

// system
#include <stdarg.h>

// TODO: the create and destroy functions arent actually used together.
// one is a pointer and the other isnt
rodeo_string_t
rodeo_string_create(const char *c_string)
{
	cstr result = cstr_NULL;
	if(c_string != NULL)
	{
		result = cstr_from(c_string);
	}
	return *(rodeo_string_t*)(&result);
}

void
rodeo_string_destroy(rodeo_string_t *self)
{
	cstr_drop((cstr*)self);
	//free(string); // the above already calls free on the entire pointer
}

char*
rodeo_string_to_cstr(rodeo_string_t *self)
{
	return cstr_data((cstr*)self);
}

const char*
rodeo_string_to_constcstr(const rodeo_string_t *self)
{
	return cstr_str((cstr*)self);
}

void
rodeo_string_insert(
	rodeo_string_t *self,
	const rodeo_string_t insert,
	intptr_t position
)
{
	cstr_insert_s((cstr*)self, position, *(cstr*)&insert);
}

void
rodeo_string_append(
	rodeo_string_t *self,
	const rodeo_string_t append
)
{
	rodeo_string_insert(
		self,
		append,
		cstr_size((cstr*)self)
	);
}

void
rodeo_string_prepend(
	rodeo_string_t *self,
	const rodeo_string_t prepend
)
{
	rodeo_string_insert(
		self,
		prepend,
		0
	);
}

void
rodeo_string_clear(rodeo_string_t *self)
{
	cstr_clear((cstr*)self);
}

void
rodeo_string_set(rodeo_string_t *self, char *value)
{
	cstr_clear((cstr*)self);
	cstr *temp = (cstr*)self;
	*temp = cstr_from(value);
}

rodeo_string_t
rodeo_string_clone(const rodeo_string_t self)
{
	cstr temp = cstr_clone(*(cstr*)&self);
	rodeo_string_t result = *(rodeo_string_t*)&temp;
	return result;
}

rodeo_string_t
rodeo_string_format(const char *format, ...)
{
	rodeo_string_t result;
	mrodeo_vargs_do(format)
	{
		cstr temp = cstr_from_vfmt(format, vargs);
		result = *(rodeo_string_t*)&temp;
	}
	return result;
}

rodeo_string_t
rodeo_string_vargs_format(const char *format, va_list vargs)
{
	cstr temp = cstr_from_vfmt(format, vargs);
	rodeo_string_t result = *(rodeo_string_t*)&temp;
	return result;
}


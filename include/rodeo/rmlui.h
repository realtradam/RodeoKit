#pragma once

// -- internal --
// public
#include "rodeo/rmlui_t.h"

// external
#include "stc/cstr.h"


void
rodeo_rmlui_init(void);

void
rodeo_rmlui_deinit(void);

void
rodeo_rmlui_font_load(cstr path);

rodeo_rmlui_document_t
rodeo_rmlui_document_load(cstr path);

void
rodeo_rmlui_document_show(rodeo_rmlui_document_t document);

void
rodeo_rmlui_update(void);

void
rodeo_rmlui_render(void);

#define \
mrodeo_rmlui_do() \
	mrodeo_defer_do(				\
		rodeo_rmlui_init(),			\
		rodeo_rmlui_deinit()		\
	)

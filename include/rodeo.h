
// public internal
#include "rodeo_types.h"

// system
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define mrodeo_name_concat(prefix, suffix) prefix##suffix
#define mrodeo_macrovar(prefix) mrodeo_name_concat(prefix##_, __LINE__)

#define mrodeo_defer_do(start, end) for(				\
		int mrodeo_macrovar(_macrovar_) = (start, 0);	\
		!mrodeo_macrovar(_macrovar_);					\
		(mrodeo_macrovar(_macrovar_) += 1), end)			\

#define								\
mrodeo_window_do(					\
	state,							\
	screen_height,					\
	screen_width,					\
	title							\
)									\
	mrodeo_defer_do(				\
		rodeo_window_init(			\
			&state,					\
			screen_height,			\
			screen_width,			\
			title					\
		),							\
		rodeo_window_deinit(state)	\
	)

void
rodeo_\
window_init(
	rodeo_data_p *state,
	int screen_height,
	int screen_width,
	char* title
);

void
rodeo_\
window_deinit(rodeo_data_p state);

void
rodeo_\
deinit(void);

#define						\
mrodeo_do(					\
	state					\
)							\
	mrodeo_defer_do(		\
		rodeo_begin(state),	\
		rodeo_end(state)	\
	)

void
rodeo_\
begin(rodeo_data_p state);

void
rodeo_\
end(rodeo_data_p state);

void
rodeo_\
mainloop_set(
	rodeo_data_p state,
	rodeo_mainloop_func main_loop_function
);

bool
rodeo_\
window_check_quit(rodeo_data_p state);

void
rodeo_\
set_quit(rodeo_data_p state, bool quit);

void
rodeo_\
debug_text_draw(uint16_t x, uint16_t y, const char *format, ...);

// rodeo_renderer_name_get
const char *
rodeo_\
renderer_name_get(void);

// rodeo_renderer_flush
void
rodeo_\
renderer_flush(rodeo_data_p state);

// rodeo_rectangle_draw
void
rodeo_\
rectangle_draw(
	rodeo_data_p state,
	uint16_t x,
	uint16_t y,
	uint16_t width,
	uint16_t height,
	rodeo_rgba_t color
);


#pragma once

// -- internal --
// private
#include "irodeo_window_t.h"

// -- external --
#include "SDL.h"
#include "SDL_syswm.h"

SDL_Window *
irodeo_window_get(void);

SDL_Surface *
irodeo_window_surface_get(void);

void
irodeo_window_dimensions_update(void);

SDL_Window *
irodeo_window_get(void);

SDL_Surface *
irodeo_window_surface_get(void);

SDL_SysWMinfo
irodeo_window_wmi_get(void);

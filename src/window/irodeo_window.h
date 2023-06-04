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
irodeo_window_screen_width_setVar(uint16_t width);

void
irodeo_window_screen_height_setVar(uint16_t height);

SDL_Window *
irodeo_window_get(void);

SDL_Surface *
irodeo_window_surface_get(void);

SDL_SysWMinfo
irodeo_window_wmi_get(void);

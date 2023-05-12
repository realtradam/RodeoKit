#pragma once
// -- external --
#include "SDL.h"
#include "SDL_mixer.h"

struct
rodeo_audio_sound_t
{
	Mix_Chunk *sdl_sound;
};

struct
rodeo_audio_music_t
{
	Mix_Music *sdl_music;
};

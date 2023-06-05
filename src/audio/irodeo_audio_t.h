#pragma once

// -- external --
#include "SDL_mixer.h"

struct
rodeo_audio_sound_data
{
	Mix_Chunk *sdl_sound;
};
struct
rodeo_audio_music_data
{
	Mix_Music *sdl_music;
};

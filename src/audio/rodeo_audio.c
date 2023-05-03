
// -- internal --
// public
#include "rodeo/audio.h"
#include "rodeo/log.h"

// -- external --
#include "SDL.h"
#include "SDL_mixer.h"

Mix_Chunk *sample_sound = NULL;

void
rodeo_audio_initialize(void)
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to initialize SDL Audio. SDL_Error: %s",
			SDL_GetError()
		);
	}
}

void
rodeo_audio_deinitialize(void)
{
	Mix_Quit();
}

void
rodeo_audio_loadSample(void)
{
	sample_sound = Mix_LoadWAV("assets/sample.wav");
	if(NULL == sample_sound)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to load sound. Mix_Error: %s",
			Mix_GetError()
		);
	}
}

void
rodeo_audio_freeSample(void)
{
	Mix_FreeChunk(sample_sound);
	sample_sound = NULL;
}

void
rodeo_audio_playSample(void)
{
	Mix_PlayChannel(-1, sample_sound, 0);
}

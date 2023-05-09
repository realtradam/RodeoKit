
// -- internal --
// public
#include "rodeo/audio.h"
#include "rodeo/log.h"
// private
#include "audio/rodeo_audio_t.h"

// -- external --
#include "SDL.h"
#include "SDL_mixer.h"

static int32_t **irodeo_audio_channelPool;

void
rodeo_audio_initialize(int32_t num_sound_pools, int32_t size_sound_pools)
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to initialize SDL Audio. SDL_Error: %s",
			SDL_GetError()
		);
	}
	else
	{
		irodeo_audio_channelPool = malloc((uint32_t)(num_sound_pools * size_sound_pools) * sizeof(int32_t));
		Mix_AllocateChannels(num_sound_pools * size_sound_pools);

		int32_t temp_channel_id = 0;
		for(int i = 0; i < num_sound_pools; ++i)
		{
			//irodeo_audio_channelPool[i] = 
			for(int j = 0; j < size_sound_pools; ++j)
			{
				irodeo_audio_channelPool[i][j] = temp_channel_id;
				temp_channel_id += 1;
			}
		}

		rodeo_audio_masterVolume_set(0.5f);
	}
}

void
rodeo_audio_deinitialize(void)
{
	Mix_Quit();
}

void
rodeo_audio_masterVolume_set(float volume_level)
{
	Mix_MasterVolume((int32_t)(volume_level * 128));
	Mix_VolumeMusic((int32_t)(volume_level * 128));
}

float
rodeo_audio_masterVolume_get(void)
{
	return ((float)Mix_MasterVolume(-1)) / (float)MIX_MAX_VOLUME;
}

rodeo_audio_sound_t*
rodeo_audio_sound_create_from_path(cstr path)
{
	rodeo_audio_sound_t *sample_sound = malloc(sizeof(rodeo_audio_sound_t));
	sample_sound->sdl_sound = Mix_LoadWAV(cstr_str(&path));
	if(NULL == sample_sound->sdl_sound)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to load sound. Mix_Error: %s",
			Mix_GetError()
		);
	}
	return sample_sound;
}

void
rodeo_audio_sound_destroy(rodeo_audio_sound_t* sound)
{
	Mix_FreeChunk(sound->sdl_sound);
	free(sound);
}

void
rodeo_audio_sound_play(rodeo_audio_sound_t *sound, int32_t pool_id)
{
	Mix_PlayChannel(pool_id, sound->sdl_sound, 0);
}

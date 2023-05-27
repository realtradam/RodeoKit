
// -- internal --
// public
#include "rodeo/audio.h"
#include "rodeo/log.h"
// private
#include "audio/rodeo_audio_t.h"

// -- external --
#include "SDL.h"
#include "SDL_mixer.h"

static uint32_t **irodeo_audio_channelPool;
//static uint32_t irodeo_audio_channelPool_num;
//static uint32_t irodeo_audio_channelPool_size;

//void
//rodeo_audio_initialize(uint32_t num_sound_pools, uint32_t size_sound_pools)
void
rodeo_audio_initialize(uint32_t channels)
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
			Mix_AllocateChannels((int32_t)channels);
		/*
		irodeo_audio_channelPool_num = 1; //num_sound_pools;
		irodeo_audio_channelPool_size = channels; //size_sound_pools;

		 void *mem_alloc =
			malloc(
				((irodeo_audio_channelPool_num) * sizeof(intptr_t)) +
				((irodeo_audio_channelPool_num * irodeo_audio_channelPool_size) * sizeof(uint32_t)
				 ));

		irodeo_audio_channelPool = mem_alloc;

		uint32_t *channelPool = (uint32_t*)(irodeo_audio_channelPool + ((irodeo_audio_channelPool_num) * sizeof(intptr_t)));

		{
			int32_t allocated_channels = 
			Mix_AllocateChannels((
				int32_t)irodeo_audio_channelPool_num * (int32_t)irodeo_audio_channelPool_size
			);

			rodeo_log(
				rodeo_logLevel_info,
				"Number of channels opened: %d",
				allocated_channels
			);
		}

		uint32_t temp_channel_id = 0;
		for(uint32_t i = 0; i < irodeo_audio_channelPool_num; ++i)
		{
			irodeo_audio_channelPool[i] =
				channelPool + (i * sizeof(uint32_t));

			for(uint32_t j = 0; j < irodeo_audio_channelPool_size; ++j)
			{
				irodeo_audio_channelPool[i][j] = temp_channel_id;
				temp_channel_id += 1;
			}

			int32_t assigning_tag_status = Mix_GroupChannel(
				(int32_t)temp_channel_id,
				(int32_t)i
			);
			if(0 == assigning_tag_status)
			{
				rodeo_log(
					rodeo_logLevel_error,
					"Failed to assign tag to sound channel. Mix_Error: %s",
					Mix_GetError()
				);
			}
		}
		*/

		// Lets not explode player's ears, yea?
		rodeo_audio_master_volume_set(0.5f);
	}
}

void
rodeo_audio_deinitialize(void)
{
	free(irodeo_audio_channelPool);
	Mix_Quit();
}

/*
uint32_t
irodeo_audio_channelPool_num_get(void)
{
	return irodeo_audio_channelPool_num;
}

uint32_t
irodeo_audio_channelPool_size_get(void)
{
	return irodeo_audio_channelPool_size;
}
*/

void
rodeo_audio_master_volume_set(float volume_level)
{
#ifndef __EMSCRIPTEN__
	Mix_MasterVolume((int32_t)(volume_level * (float)MIX_MAX_VOLUME));
	Mix_VolumeMusic((int32_t)(volume_level * (float)MIX_MAX_VOLUME));
#endif
}

float
rodeo_audio_master_volume_get(void)
{
#ifndef __EMSCRIPTEN__
	return ((float)Mix_MasterVolume(-1)) / (float)MIX_MAX_VOLUME;
#elif
	return 0.0f
#endif
}

/*
void
rodeo_audio_channelPool_volume_set(uint32_t channel_pool_id, float volume_level)
{
	for(uint32_t i = 0; i < irodeo_audio_channelPool_size; i += 1)
	{
		Mix_Volume((int32_t)irodeo_audio_channelPool[channel_pool_id][i], (int32_t)(volume_level * (float)MIX_MAX_VOLUME));
	}
}

float
rodeo_audio_channelPool_volume_get(uint32_t channel_pool_id)
{
	return ((float)Mix_Volume((int32_t)channel_pool_id, -1) /
				(float)MIX_MAX_VOLUME);
}
*/

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

rodeo_audio_music_t*
rodeo_audio_music_create_from_path(cstr path)
{
	rodeo_audio_music_t *sample_music = malloc(sizeof(rodeo_audio_music_t));
	sample_music->sdl_music = Mix_LoadMUS(cstr_str(&path));
	if(NULL == sample_music->sdl_music)
	{
		rodeo_log(
			rodeo_logLevel_error,
			"Failed to load music. Mix_Error: %s",
			Mix_GetError()
		);
	}
	return sample_music;
}

void
rodeo_audio_music_destroy(rodeo_audio_music_t* music)
{
	Mix_FreeMusic(music->sdl_music);
	free(music);
}


void
rodeo_audio_sound_play(rodeo_audio_sound_t *sound) //, uint32_t channel_pool_id)
{
	Mix_PlayChannel(-1, sound->sdl_sound, 0);
}

void
rodeo_audio_music_play(rodeo_audio_music_t *music) //, uint32_t channel_pool_id)
{
	rodeo_audio_music_stop();
	Mix_PlayMusic(music->sdl_music, 0);
}

void
rodeo_audio_music_play_fadeIn(rodeo_audio_music_t *music, uint32_t fade_duration_milliseconds)
{
	rodeo_audio_music_stop();
	Mix_FadeInMusic(music->sdl_music, 0, (int32_t)fade_duration_milliseconds);
}

void
rodeo_audio_music_stop(void)
{
	Mix_HaltMusic();
}

bool
rodeo_audio_music_isPlaying(void)
{
	return Mix_PlayingMusic();
}

void
rodeo_audio_music_stop_fadeOut(uint32_t fade_duration_milliseconds)
{
	Mix_FadeOutMusic((int32_t)fade_duration_milliseconds);
}

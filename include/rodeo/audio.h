#pragma once

// -- external --
#include "stc/cstr.h"

// -- system --
#include <inttypes.h>

typedef struct rodeo_audio_sound_t rodeo_audio_sound_t;
typedef struct rodeo_audio_music_t rodeo_audio_music_t;

void
rodeo_audio_initialize(
	uint32_t channels
	//uint32_t num_sound_pools,
	//uint32_t size_sound_pools
);

void
rodeo_audio_deinitialize(void);

/*
uint32_t
irodeo_audio_channelPool_num_get(void);

uint32_t
irodeo_audio_channelPool_size_get(void);
*/

void
rodeo_audio_master_volume_set(float volume_level);

float
rodeo_audio_master_volume_get(void);

/*
void
rodeo_audio_channelPool_volume_set(uint32_t channel_pool_id, float volume_level);

float
rodeo_audio_channelPool_volume_get(uint32_t channel_pool_id);
*/

rodeo_audio_sound_t*
rodeo_audio_sound_create_from_path(cstr path);

void
rodeo_audio_sound_destroy(rodeo_audio_sound_t* sound);

rodeo_audio_music_t*
rodeo_audio_music_create_from_path(cstr path);

void
rodeo_audio_music_destroy(rodeo_audio_music_t* music);

void
rodeo_audio_sound_play(rodeo_audio_sound_t *sound);

void
rodeo_audio_music_play(rodeo_audio_music_t *music);

void
rodeo_audio_music_play_fadeIn(rodeo_audio_music_t *music, uint32_t fade_duration_milliseconds);

void
rodeo_audio_music_stop(void);

void
rodeo_audio_music_stop_fadeOut(uint32_t fade_duration_milliseconds);

bool
rodeo_audio_music_isPlaying(void);

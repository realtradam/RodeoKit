#pragma once

// -- external --
#include "stc/cstr.h"

// -- system --
#include <inttypes.h>

typedef struct rodeo_audio_sound_t rodeo_audio_sound_t;

void
rodeo_audio_initialize(
	int32_t num_sound_pools,
	int32_t size_sound_pools
);

void
rodeo_audio_deinitialize(void);

void
rodeo_audio_masterVolume_set(float volume_level);

float
rodeo_audio_masterVolume_get(void);

rodeo_audio_sound_t*
rodeo_audio_sound_create_from_path(cstr path);

void
rodeo_audio_sound_destroy(rodeo_audio_sound_t* sound);

void
rodeo_audio_sound_play(rodeo_audio_sound_t *sound, int32_t pool_id);

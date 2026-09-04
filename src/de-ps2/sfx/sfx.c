/**
* @file sfx.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "sfx.h"
static int channel = -1;
static u8 music_cache_count = 0;
static u8 sound_cache_count = 0;
static music_cache_entry_t music_cache[SFX_MUSIC_CACHE_SIZE];
static sound_cache_entry_t sound_cache[SFX_SOUND_CACHE_SIZE];

void sfx_init(void) {
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        printf("ERROR: Mixer initialization failed: %s\n", Mix_GetError());
        return;
    }
    // PS2-optimized audio settings
    // MIX_DEFAULT_FORMAT: Usually 16-bit signed
    // 2: Stereo channels
    // 3096: Larger buffer for PS2's slower I/O and processing
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 3096) < 0) {
        printf("ERROR: Mixer initialization failed: %s\n", Mix_GetError());
        return;
    }
    Mix_AllocateChannels(MIX_DEFAULT_CHANNELS); // Limit to 2 simultaneous sound effects
}

void sfx_play_music(music_t music) {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(music.music, -1);
	}
}

void sfx_play_sound(sound_t sound) {
    channel = Mix_PlayChannel(-1, sound.audio, 0);
}

void sfx_play_music_cached(string_t path) {
    for (u8 i = 0; i < music_cache_count; i++) {
        if (strcmp(music_cache[i].path, path) == 0) {
            printf("OK: Using cached music for path: %s\n", path);
            sfx_play_music(music_cache[i].music);
            return;
        }
    }

    music_t music = load_music_t(path);
    if (music.music == NULL) {
        return;
    }

    if (music_cache_count < SFX_MUSIC_CACHE_SIZE) {
       music_cache[music_cache_count].path = path;
       music_cache[music_cache_count].music = music;
       sfx_play_music(music_cache[music_cache_count].music);
       music_cache_count++;
       printf("OK: Cached music added for path: %s\n", path);
    }
}

void sfx_play_sound_cached(string_t path) {
    for (u8 i = 0; i < sound_cache_count; i++) {
        if (strcmp(sound_cache[i].path, path) == 0) {
            printf("OK: Using cached sound for path: %s\n", path);
            sfx_play_sound(sound_cache[i].sound);
            return;
        }
    }
    
    sound_t sound = load_sound_t(path);
    if (sound.audio == NULL) {
        return;
    }
    
    if (sound_cache_count >= SFX_SOUND_CACHE_SIZE) {
        return;
    }

    sound_cache[sound_cache_count].path = path;
    sound_cache[sound_cache_count].sound = sound;
    sfx_play_sound(sound_cache[sound_cache_count].sound);
    sound_cache_count++;
    printf("OK: Cached sound added for path: %s\n", path);
}

void sfx_cache_music(string_t path) {
    if (music_cache_count >= SFX_MUSIC_CACHE_SIZE) {
        return;
    }

    for (u8 i = 0; i < music_cache_count; i++) {
        if (strcmp(music_cache[i].path, path) == 0) {
            printf("OK: music already cached for path: %s\n", path);
            return;
        }
    }

    music_t music = load_music_t(path);
    if (music.music == NULL) {
        return;
    }

    music_cache[music_cache_count].path = path;
    music_cache[music_cache_count].music = music;
    music_cache_count++;
    printf("OK: Cached music added for path: %s\n", path);
}

void sfx_cache_sound(string_t path) {
    if (sound_cache_count >= SFX_SOUND_CACHE_SIZE) {
        return;
    }

    for (u8 i = 0; i < sound_cache_count; i++) {
        if (strcmp(sound_cache[i].path, path) == 0) {
            printf("OK: sound already cached for path: %s\n", path);
            return;
        }
    }

    sound_t sound = load_sound_t(path);
    if (sound.audio == NULL) {
        return;
    }

    sound_cache[sound_cache_count].path = path;
    sound_cache[sound_cache_count].sound = sound;
    sound_cache_count++;
    printf("OK: Cached sound added for path: %s\n", path);
}

void sfx_stop_all(void) {
    sfx_stop_music();
    sfx_stop_sound();
}

void sfx_stop_music(void) {
	Mix_HaltMusic();
}

void sfx_stop_sound(void) {
	Mix_HaltChannel(channel);
}

u8 sfx_get_music_cache_count(void) {
    return music_cache_count;
}

u8 sfx_get_sound_cache_count(void) {
    return sound_cache_count;
}

void sfx_clear_music_cache(void) {
    for (u8 i = 0; i < music_cache_count; i++) {
        if (music_cache[i].music.music != NULL) {
            unload_music_t(music_cache[i].music);
            music_cache[i].music.music = NULL;
        }
    }
    music_cache_count = 0;
}

void sfx_clear_sound_cache(void) {
    for (u8 i = 0; i < sound_cache_count; i++) {
        if (sound_cache[i].sound.audio != NULL) {
            unload_sound_t(sound_cache[i].sound);
            sound_cache[i].sound.audio = NULL;
        }
    }
    sound_cache_count = 0;
}

void sfx_quit(void) {
    channel = -1;
    sfx_clear_music_cache();
    sfx_clear_sound_cache();
    Mix_HaltChannel(-1);
    Mix_CloseAudio();
    Mix_Quit();
}

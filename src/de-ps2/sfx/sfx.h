/**
 * @file sfx.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_SFX_H
#define DE_SFX_H

#include "../de.h"
#include "../io/loader.h"
#include "../core/types.h"

#define SFX_MUSIC_CACHE_SIZE 8
#define SFX_SOUND_CACHE_SIZE 8

typedef struct music_cache_entry_t {
    string_t path;
    music_t music;
} music_cache_entry_t;

typedef struct sound_cache_entry_t {
    string_t path;
    sound_t sound;
} sound_cache_entry_t;

void sfx_init(void);
void sfx_quit(void);

void sfx_play_music(music_t music);
void sfx_play_sound(sound_t sound);

void sfx_play_music_cached(string_t path);
void sfx_play_sound_cached(string_t path);

void sfx_cache_music(string_t path);
void sfx_cache_sound(string_t path);

void sfx_stop_all(void);
void sfx_stop_music(void);
void sfx_stop_sound(void);

u8 sfx_get_music_cache_count(void);
u8 sfx_get_sound_cache_count(void);
void sfx_clear_music_cache(void);
void sfx_clear_sound_cache(void);

#endif /* DE_SFX_H */

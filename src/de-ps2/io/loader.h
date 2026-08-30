/**
* @file loader.h
* @author Hudson Schumaker
* @version 1.0.0
* @copyright Copyright (c) 2026, Dodoi-Lab
*/
#ifndef DE_LOADER_H
#define DE_LOADER_H
#include "../de.h"
#include "../util/types.h"
#include "../core/context.h"

texture_t load_texture_t(string_t path);
void unload_texture_t(texture_t texture);

sound_t load_sound_t(string_t path);
void unload_sound_t(sound_t sound);

music_t load_music_t(string_t path);
void unload_music_t(music_t music);

font_t load_font_t(string_t path, int size);
void unload_font_t(font_t font);

#endif /* DE_LOADER_H */

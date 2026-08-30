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

void sfx_init(void);

void sfx_load_music(const char* path);
void sfx_load_sound(const char* path);

void sfx_play_music(void);
void sfx_play_sound(void);

void sfx_stop_music(void);
void sfx_stop_sound(void);

#endif /* DE_SFX_H */

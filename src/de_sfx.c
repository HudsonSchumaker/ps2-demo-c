/**
* @file sfx.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_sfx.h"

static Mix_Music* music = NULL;
static Mix_Chunk* sound = NULL;
static int channel = -1;

void sfx_init(void) {
	// PS2-optimized audio settings
    // MIX_DEFAULT_FORMAT: Usually 16-bit signed
    // 2: Stereo channels
    // 2048: Larger buffer for PS2's slower I/O and processing
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("ERROR: Mixer initialization failed: %s\n", Mix_GetError());
        return;
    }
    Mix_AllocateChannels(2); // Limit to 2 simultaneous sound effects
}

void sfx_load_music(const char* file_path) {
    // Free existing music if loaded
    if (music) {
        Mix_FreeMusic(music);
        music = NULL;
    }
    
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        printf("ERROR: fopen failed for music: %s\n", file_path);
        return;
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE); // SDL_TRUE = auto close
    if (!rw) {
        printf("ERROR: SDL_RWFromFP failed for music!\n");
        fclose(file);
        return;
    }
    
    // Load music file using RWops
    music = Mix_LoadMUS_RW(rw, 1); // 1 = auto free rw
    if (!music) {
        printf("ERROR: Failed to load music: %s\n", Mix_GetError());
        return;
    }
}

void sfx_load_sound(const char* file_path) {
    // Free existing sound if loaded
    if (sound) {
        Mix_FreeChunk(sound);
        sound = NULL;
    }

    FILE* file = fopen(file_path, "rb");
    if (!file) {
        printf("ERROR: fopen failed for sound: %s\n", file_path);
        return;
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE); // SDL_TRUE = auto close
    if (!rw) {
        printf("ERROR: SDL_RWFromFP failed for sound!\n");
        return;
    }

    sound = Mix_LoadWAV_RW(rw, 1); // 1 = auto free rw
    if (!sound) {
        printf("ERROR: Mix_LoadWAV_RW failed: %s\n", Mix_GetError());
    }
}

void sfx_play_music(void) {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(music, -1);
	}
}

void sfx_play_sound(void) {
	channel = Mix_PlayChannel(-1, sound, 0);
}

void sfx_stop_music(void) {
	Mix_HaltMusic();
}

void sfx_stop_sound(void) {
	Mix_HaltChannel(channel);
}

void sfx_close(void) {
	Mix_FreeMusic(music);
	Mix_FreeChunk(sound);
    Mix_HaltChannel(-1);
	Mix_CloseAudio();
	Mix_Quit();
}

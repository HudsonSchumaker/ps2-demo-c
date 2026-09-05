/**
* @file loader.c
* @brief Implementation of resource loading functions in C.
* @author Hudson Schumaker
* @version 1.0.0
* @copyright Copyright (c) 2026, Dodoi-Lab
*/
#include "loader.h"

texture_t load_texture_t(string_t path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        return (texture_t){0};
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE); 
    if (!rw) {
        fclose(file);
        return (texture_t){0};
    }

    SDL_Surface* surface = IMG_Load_RW(rw, 1); // 1 = auto free rw
    if (!surface) {
        return (texture_t){0};
    }

    SDL_Surface* ps2_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB565, 0);
    SDL_Texture* ps2_texture = SDL_CreateTextureFromSurface(ctx_get_renderer(), ps2_surface);

    SDL_Rect rect;
    SDL_QueryTexture(ps2_texture, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(ps2_surface);

    return (texture_t){ 
        .position.x = 0, 
        .position.y = 0, 
        .size.w = rect.w, 
        .size.h = rect.h,
        .texture = ps2_texture 
    };
}

void unload_texture_t(texture_t texture) {
    SDL_DestroyTexture(texture.texture);
}

sound_t load_sound_t(string_t path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("ERROR: fopen failed for sound: %s\n", path);
        return (sound_t){0};
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE); // SDL_TRUE = auto close
    if (!rw) {
        printf("ERROR: SDL_RWFromFP failed for sound: %s\n", path);
        return (sound_t){0};
    }

    Mix_Chunk* sound = Mix_LoadWAV_RW(rw, 1); // 1 = auto free rw
    if (!sound) {
        printf("ERROR: Mix_LoadWAV_RW failed for sound: %s\n", path);
        return (sound_t){0};
    }

    return (sound_t){ .audio = sound };
}

void unload_sound_t(sound_t sound) {
    Mix_FreeChunk(sound.audio);
}

music_t load_music_t(string_t path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("ERROR: fopen failed for music: %s\n", path);
        return (music_t){0};
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE); // SDL_TRUE = auto close
    if (!rw) {
        printf("ERROR: SDL_RWFromFP failed for music!\n");
        return (music_t){0};
    }
    
    Mix_Music* music = Mix_LoadMUS_RW(rw, 1); // 1 = auto free rw, WAV is fully buffered
    if (!music) {
        printf("ERROR: Failed to load music: %s\n", Mix_GetError());
        return (music_t){0};
    }

    printf("OK: music loaded\n");
    return (music_t){ .music = music };
}

void unload_music_t(music_t music) {
    Mix_FreeMusic(music.music);
}

font_t load_font_t(string_t path, int size) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("ERROR: fopen failed for font: %s\n", path);
        return (font_t){0};
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE);
    if (!rw) {
        printf("ERROR: SDL_RWFromFP failed for font!\n");
        return (font_t){0};
    }

    TTF_Font* font = TTF_OpenFontRW(rw, 1, size);
    if (!font) {
        printf("ERROR: TTF_OpenFontRW failed: %s\n", TTF_GetError());
        return (font_t){0};
    }

    font_t font_struct = { .font = font, .size = size };
    return font_struct;
}

void unload_font_t(font_t font) {
    TTF_CloseFont(font.font);
}

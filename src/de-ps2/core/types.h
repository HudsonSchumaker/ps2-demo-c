/**
 * @file types.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2026, Dodoi-Lab
 */
#ifndef DE_TYPES_H
#define DE_TYPES_H

#include "../de.h"

typedef struct ipoint_t {
    union {
        struct {
            int x;
            int y;
        };
        int values[2];
    };
    
} ipoint_t;

typedef struct fpoint_t {
    union {
        struct {
            float x;
            float y;
        };
        float values[2];
    };
} fpoint_t;

typedef struct idimension_t {
    union {
        struct {
            int w;
            int h;
        };
        int values[2];
    };
} idimension_t;

typedef struct fdimension_t {
    union {
        struct {
            float w;
            float h;
        };
        float values[2];
    };
} fdimension_t;

typedef struct rect_t {
    int x;
    int y;
    int w;
    int h;
} rect_t;

typedef struct ipair_t {
    union {
        struct {
            int f;
            int s;
        };
        int values[2];
    };
} ipair_t;

typedef struct fpair_t {
    union {
        struct {
            float f;
            float s;
        };
        float values[2];
    };
} fpair_t;

typedef struct itriple_t {
    union {
        struct {
            int f;
            int s;
            int t;
        };
        int values[3];
    };
} itriple_t;

typedef struct ftriple_t {
    union {
        struct {
            float f;
            float s;
            float t;
        };
        float values[3];
    };
} ftriple_t;

typedef union vec2_t {
    struct {
        f32 x;
        f32 y;
    };
    f32 v[2];
} vec2_t;

typedef union vec3_t {
    struct {
        f32 x;
        f32 y;
        f32 z;
    };
    f32 v[3];
} vec3_t;

typedef union vec4_t {
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    f32 v[4];
} vec4_t;

typedef struct texture_t {
    fdimension_t size;
    SDL_Texture* texture;
} texture_t;

typedef struct font_t {
    TTF_Font* font;
    int size;
} font_t;

typedef struct label_t {
    ipoint_t position;
    fdimension_t size;
    SDL_Texture* texture;
} label_t;

typedef struct sound_t {
    Mix_Chunk* audio;
} sound_t;

typedef struct music_t {
    Mix_Music* music;
} music_t;

#endif /* DE_TYPES_H */

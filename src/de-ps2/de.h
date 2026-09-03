/**
* @file de.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_H
#define DE_H

// Libc
#include <math.h>
#include <time.h>
#include <float.h>
#include <stdio.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// PS2 includes
#include <kernel.h>
#include <sifrpc.h>
#include <iopheap.h>
#include <tamtypes.h>
#include <loadfile.h>

// SDL2 includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_gamecontroller.h>
#ifndef SDL_HINT_PS2_GS_MODE
#define SDL_HINT_PS2_GS_MODE "SDL_PS2_GS_MODE"
#endif
#ifndef SDL_HINT_PS2_GS_WIDTH
#define SDL_HINT_PS2_GS_WIDTH "SDL_PS2_GS_WIDTH"
#endif
#ifndef SDL_HINT_PS2_GS_HEIGHT
#define SDL_HINT_PS2_GS_HEIGHT "SDL_PS2_GS_HEIGHT"
#endif
#ifndef SDL_HINT_PS2_GS_PROGRESSIVE
#define SDL_HINT_PS2_GS_PROGRESSIVE "SDL_PS2_GS_PROGRESSIVE"
#endif

// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_H_WIDTH 320
#define SCREEN_HEIGHT 448
#define SCREEN_H_HEIGHT 224

// Fast math division
#define DIV2   0.5f
#define DIV3   0.3333333333f
#define DIV4   0.25f
#define DIV5   0.2f
#define DIV6   0.1666666667f
#define DIV7   0.1428571429f
#define DIV8   0.125f
#define DIV9   0.1111111111f
#define DIV10  0.1f
#define DIV16  0.0625f
#define DIV32  0.03125f
#define DIV64  0.015625f
#define DIV128 0.0078125f

#define PI_F 3.1415927f
#define TWO_PI_F (PI_F * 2.0f)
#define HALF_PI_F (PI_F * 0.5f)
#define DEG_2_RAD_F (PI_F / 180.0f)
#define RAD_2_DEG_F (180.0f / PI_F)
#define EPSILON_F 0.00001f

typedef uint8_t  byte;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float   f32;
typedef double  f64;
typedef char*   text_t;
typedef const char* string_t;

// Navigation Definitions
#define QUIT -2
#define EXIT -1
#define NADA 0
#define NEXT 1
#define BACK 2
#define PLAY 3
#define PAUSE 4
#define RESUME 5
#define RESTART 6
#define CONTINUE 7
#define GAME_OVER 8
#define RELOAD 9

#endif /* DE_H */

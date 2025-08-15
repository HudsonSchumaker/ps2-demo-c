/**
* @file pch.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/

#pragma once
// PS2 includes
#include <kernel.h>
#include <sifrpc.h>
#include <tamtypes.h>

// Libc
#include <time.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// SDL2 includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_gamecontroller.h>

// Project 
typedef uint8_t byte;

// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_H_WIDTH 320
#define SCREEN_HEIGHT 448
#define SCREEN_H_HEIGHT 224

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

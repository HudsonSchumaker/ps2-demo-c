/**
* @file camera.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
    short x, y, w, h;
    SDL_Color color;
} camera_t;

void camera_init(camera_t* camera) {
    camera->x = 0;
    camera->y = 0;
    camera->w = SCREEN_WIDTH;
    camera->h = SCREEN_HEIGHT;
    camera->color = (SDL_Color){0, 0, 255, 255};
}

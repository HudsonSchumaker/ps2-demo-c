/**
 * @file camera.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_CAMERA_H
#define DE_CAMERA_H

#include "../de.h"
#include "../gfx/color.h"

typedef struct camera_t {
    int x;
    int y;
    int w;
    int h;
    color_t background_color;
} camera_t;

camera_t camera_create(color_t color);

#endif /* DE_CAMERA_H */

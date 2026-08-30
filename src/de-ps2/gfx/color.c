/**
 * @file color.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "color.h"

color_t color_RGB(uint8_t r, uint8_t g, uint8_t b) {
    color_t color = {r, g, b, 255};
    return color;
}

color_t color_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    color_t color = {r, g, b, a};
    return color;
}

SDL_Color color_2_sdl_color(const color_t color) {
    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};
    return sdl_color;
}

color_t color_red(void) {
    return color_RGB(255, 0, 0);
}

color_t color_green(void) {
    return color_RGB(0, 255, 0);
}

color_t color_blue(void) {
    return color_RGB(0, 0, 255);
}

color_t color_white(void) {
    return color_RGB(255, 255, 255);
}

color_t color_black(void) {
    return color_RGB(0, 0, 0);
}

color_t color_gray(void) {
    return color_RGB(128, 128, 128);
}

color_t color_yellow(void) {
    return color_RGB(255, 255, 0);
}

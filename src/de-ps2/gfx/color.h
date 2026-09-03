#ifndef DE_COLOR_H
#define DE_COLOR_H

#include "../de.h"

typedef struct color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color_t;

color_t color_RGB(uint8_t r, uint8_t g, uint8_t b);
color_t color_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

SDL_Color color_2_sdl_color(const color_t color);

color_t color_red(void);
color_t color_green(void);
color_t color_blue(void);
color_t color_white(void);
color_t color_black(void);
color_t color_gray(void);
color_t color_yellow(void);

#endif /* DE_COLOR_H */

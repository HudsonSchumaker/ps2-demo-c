/**
 * @file draw.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2026, Dodoi-Lab
 */
#ifndef DE_DRAW_H
#define DE_DRAW_H

#include "../de.h"
#include "color.h"
#include "../core/context.h"

void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, color_t color);
void draw_dashed_line(i32 x0, i32 y0, i32 x1, i32 y1, i16 dash_length, color_t color);
void draw_circle(i32 cx, i32 cy, i32 radius, color_t color);
void draw_fill_circle(i32 cx, i32 cy, i32 radius, color_t color);
void draw_dashed_circle(i32 cx, i32 cy, i32 radius, i32 dash_length, color_t color);
void draw_box(SDL_Rect rect, color_t color);
void draw_fbox(SDL_FRect rect, color_t color);
void draw_fill_box(SDL_Rect rect, color_t color);
void draw_fill_fbox(SDL_FRect rect, color_t color);
void draw_triangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, color_t color);

#endif /* DE_DRAW_H */

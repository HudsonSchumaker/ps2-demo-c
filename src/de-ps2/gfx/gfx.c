/**
 * @file gfx.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "gfx.h"

#define GFX_TEXTURE_CACHE_SIZE 32

SDL_Rect gfx_get_texture_size(SDL_Texture* texture) {
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = 0;
    rect.y = 0;
    return rect;
}

SDL_FRect gfx_get_texture_fsize(SDL_Texture* texture) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_FRect rect;
    rect.x = 0.0f;
    rect.y = 0.0f;
    rect.w = (float)w;
    rect.h = (float)h;
    return rect;
}

void gfx_render_texture(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h) {
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(ctx_get_renderer(), texture, NULL, &dest);
}

void gfx_render_texture_rotated(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h, f64 angle) {
    SDL_Rect dest = {x, y, w, h};
    SDL_Point center = {w >> 1, h >> 1};
    SDL_RenderCopyEx(ctx_get_renderer(), texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);
}

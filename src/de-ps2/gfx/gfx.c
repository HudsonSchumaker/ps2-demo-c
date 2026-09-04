/**
 * @file gfx.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "gfx.h"
static u8 texture_cache_count = 0;
static texture_cache_entry_t texture_cache[GFX_TEXTURE_CACHE_SIZE];

texture_t gfx_load_texture_cached(string_t path) {
    for (u8 i = 0; i < texture_cache_count; i++) {
        if (strcmp(texture_cache[i].path, path) == 0) {
            printf("OK: Texture found in cache: %s\n", path);
            return texture_cache[i].texture;
        }
    }

    // Even if the texture is not in the cache, still loads it from the path
    // If the cache is full, we simply do not store the new texture in the cache, but return it anyway
    texture_t texture = load_texture_t(path);
    if (texture.texture == NULL) {
        return (texture_t){0};
    }

    if (texture_cache_count < GFX_TEXTURE_CACHE_SIZE) {
        texture_cache[texture_cache_count].path = path;
        texture_cache[texture_cache_count].texture = texture;
        texture_cache_count++;
        printf("OK: Texture added to cache: %s\n", path);
    }

    return texture;
}

u8 gfx_get_texture_cache_count(void) {
    return texture_cache_count;
}

void gfx_clear_texture_cache(void) {
    for (u8 i = 0; i < texture_cache_count; i++) {
        if (texture_cache[i].texture.texture != NULL) {
            SDL_DestroyTexture(texture_cache[i].texture.texture);
        }
    }
    texture_cache_count = 0;
}

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

void gfx_render_texture(texture_t texture) {
    SDL_Rect dest = {.x = texture.position.x, .y = texture.position.y, .w = texture.size.w, .h = texture.size.h };
    SDL_RenderCopy(ctx_get_renderer(), texture.texture, NULL, &dest);
}

void gfx_render_texture_rotated(texture_t texture, f64 angle) {
    SDL_Rect dest = {.x = texture.position.x, .y = texture.position.y, .w = texture.size.w, .h = texture.size.h};
    SDL_Point center = {dest.w >> 1, dest.h >> 1};
    SDL_RenderCopyEx(ctx_get_renderer(), texture.texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);
}

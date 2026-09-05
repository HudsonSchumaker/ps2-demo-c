/**
 * @file gfx.h
 * @author Hudson Schumaker
 * @version 1.1.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_GFX_H
#define DE_GFX_H

#include "color.h"
#include "../de.h"
#include "../io/loader.h"
#include "../core/context.h"

#define GFX_TEXTURE_CACHE_SIZE 48

typedef struct texture_cache_entry_t {
    string_t path;
    texture_t texture;
} texture_cache_entry_t;

// Load texture with cache
texture_t gfx_load_texture_cached(string_t path);
u8 gfx_get_texture_cache_count(void);
void gfx_clear_texture_cache(void);
void gfx_cache_texture(string_t path);

// Query texture size
SDL_Rect gfx_get_texture_size(SDL_Texture* texture);
SDL_FRect gfx_get_texture_fsize(SDL_Texture* texture);

// Render textures
void gfx_render_texture(texture_t texture);
void gfx_render_texture_rotated(texture_t texture, f64 angle);

#endif /* DE_GFX_H */

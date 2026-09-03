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

// Query texture size
SDL_Rect gfx_get_texture_size(SDL_Texture* texture);
SDL_FRect gfx_get_texture_fsize(SDL_Texture* texture);

// Render textures
void gfx_render_texture(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h);
void gfx_render_texture_rotated(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h, f64 angle);

#endif /* DE_GFX_H */

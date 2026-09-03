/**
 * @file write.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "write.h"

label_t write_create_text(string_t path, string_t text, u8 text_size, color_t color) {
    font_t font = load_font_t(path, text_size);
    SDL_Surface* surface = TTF_RenderText_Solid(font.font, text, (SDL_Color){color.r, color.g, color.b, color.a});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx_get_renderer(), surface);
    SDL_FRect rect = gfx_get_texture_fsize(texture);

    label_t label;
    label.texture = texture;
    label.position = (ipoint_t){.x = 0, .y = 0};
    label.size = (fdimension_t){.w = rect.w, .h = rect.h};

    SDL_FreeSurface(surface);
    unload_font_t(font);
    return label;
}

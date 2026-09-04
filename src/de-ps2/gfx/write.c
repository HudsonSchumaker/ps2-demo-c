/**
 * @file write.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "write.h"
static u8 font_cache_count = 0;
static font_cache_entry_t font_cache[WRITE_FONT_CACHE_SIZE];

static label_t write_create_text_font(font_t font, string_t text, color_t color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font.font, text, (SDL_Color){color.r, color.g, color.b, color.a});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx_get_renderer(), surface);
    SDL_Rect rect = gfx_get_texture_size(texture);

    label_t label;
    label.texture = texture;
    label.position = (ipoint_t){.x = 0, .y = 0};
    label.size = (idimension_t){.w = rect.w, .h = rect.h};

    SDL_FreeSurface(surface);
    return label;
}

label_t write_create_text(string_t path, string_t text, u8 text_size, color_t color) {
    font_t font = load_font_t(path, text_size);
    label_t label = write_create_text_font(font, text, color);
    unload_font_t(font);
    return label;
}

label_t write_create_text_cached(string_t path, string_t text, u8 text_size, color_t color) {
    for (i8 i = 0; i < WRITE_FONT_CACHE_SIZE; i++) {
        if (font_cache[i].font.size == text_size) {
            if (strcmp(font_cache[i].path, path) == 0) {
                printf("OK: Font found in cache: %s\n", path);
                return write_create_text_font(font_cache[i].font, text, color);
            }
        }
    }

    font_t font = load_font_t(path, text_size);
    if (font.font == NULL) {
        return (label_t){0};
    }

    if (font_cache_count < WRITE_FONT_CACHE_SIZE) {
        font_cache[font_cache_count].path = path;
        font_cache[font_cache_count].font = font;
        font_cache_count++;
        printf("OK: Font added to cache: %s\n", path);
    }
    return write_create_text_font(font, text, color);
}

void write_cache_font(string_t path, u8 text_size) {
    if (font_cache_count >= WRITE_FONT_CACHE_SIZE) {
        return;
    }

    for (i8 i = 0; i < WRITE_FONT_CACHE_SIZE; i++) {
        if (font_cache[i].font.size == text_size) {
            if (strcmp(font_cache[i].path, path) == 0) {
                printf("OK: Font already in cache: %s\n", path);
                return;
            }
        }
    }

    font_t font = load_font_t(path, text_size);
    if (font.font == NULL) {
        return;
    }

    font_cache[font_cache_count].path = path;
    font_cache[font_cache_count].font = font;
    font_cache_count++;
    printf("OK: Font added to cache: %s\n", path);
    
}

void write_render_text(label_t label) {
    SDL_Rect dst_rect = {
        label.position.x,
        label.position.y,
        label.size.w,
        label.size.h
    };
    SDL_RenderCopy(ctx_get_renderer(), label.texture, NULL, &dst_rect);
}

u8 write_get_font_cache_count(void) {
    return font_cache_count;
}

void write_clear_font_cache(void) {
    for (u8 i = 0; i < font_cache_count; i++) {
        if (font_cache[i].font.font != NULL) {
            TTF_CloseFont(font_cache[i].font.font);
        }
    }
    font_cache_count = 0;
}

void write_destroy_text(label_t label) {
    if (label.texture != NULL) {
        SDL_DestroyTexture(label.texture);
    }
}

/**
 * @file write.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2026, Dodoi-Lab
*/
#ifndef DE_WRITE_H
#define DE_WRITE_H

#include "../de.h"
#include "color.h"
#include "../gfx/gfx.h"
#include "../io/loader.h"
#include "../core/types.h"
#include "../core/context.h"

#define WRITE_FONT_CACHE_SIZE 8

typedef struct font_cache_entry_t {
    string_t path;
    font_t font;
} font_cache_entry_t;

label_t write_create_text(string_t path, string_t text, u8 text_size, color_t color);
label_t write_create_text_cached(string_t path, string_t text, u8 text_size, color_t color);

void write_render_text(label_t label);

u8 write_get_font_cache_count(void);
void write_cache_font(string_t path, u8 text_size);
void write_clear_font_cache(void);
void write_destroy_text(label_t label);

#endif /* DE_WRITE_H */

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

label_t write_create_text(string_t path, string_t text, u8 text_size, color_t color);

#endif /* DE_WRITE_H */

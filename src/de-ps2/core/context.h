/**
 * @file context.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#ifndef DE_CONTEXT_H
#define DE_CONTEXT_H

#include "../de.h"
#include "input.h"
#include "../gfx/gfx.h"
#include "../sfx/sfx.h"
#include "../gfx/write.h"

bool ctx_init(void);
void ctx_quit(void);

SDL_Window* ctx_get_window(void);
SDL_Renderer* ctx_get_renderer(void);

#endif /* DE_CONTEXT_H */

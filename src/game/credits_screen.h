/**
 * @file credits_screen.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#ifndef CREDITS_SCREEN_H
#define CREDITS_SCREEN_H

#include "../app.h"
#include "../de-ps2/gfx/gfx.h"
#include "../de-ps2/gfx/write.h"
#include "../de-ps2/gfx/scene.h"
#include "../de-ps2/core/engine.h"

void credits_screen_init(void);
void credits_screen_load(void);
void credits_screen_input(void);
void credits_screen_update(void);
void credits_screen_render(void);
byte credits_screen_run(void);
void credits_screen_unload(void);
scene_t* credits_screen_get_scene(void);

#endif /* CREDITS_SCREEN_H */

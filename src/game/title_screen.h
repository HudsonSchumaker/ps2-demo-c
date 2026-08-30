/**
* @file title_screen.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H
#include "../app.h"
#include "../de-ps2/sfx/sfx.h"
#include "../de-ps2/gfx/scene.h"
#include "../de-ps2/io/loader.h"
#include "../de-ps2/util/types.h"
#include "../de-ps2/core/input.h"
#include "../de-ps2/core/engine.h"
#include "../de-ps2/core/context.h"

void title_screen_init(void);
void title_screen_load(void);
void title_screen_input(void);
void title_screen_update(void);
void title_screen_render(void);
byte title_screen_run(void);
void title_screen_unload(void);

scene_t* title_screen_get_scene(void);

#endif /* TITLE_SCREEN_H */

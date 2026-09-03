/**
* @file splash_screen.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "../app.h"
#include "../de-ps2/gfx/scene.h"
#include "../de-ps2/io/loader.h"
#include "../de-ps2/core/engine.h"
#include "../de-ps2/core/context.h"

void splash_screen_init(void);
void splash_screen_load(void);
void splash_screen_input(void);
void splash_screen_update(void);
void splash_screen_render(void);
byte splash_screen_run(void);
void splash_screen_unload(void);
scene_t* splash_screen_get_scene(void);

#endif /* SPLASH_SCREEN_H */

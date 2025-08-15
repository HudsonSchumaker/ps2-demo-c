/**
* @file title_screen.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_scene.h"

void title_screen_init(void);
void title_screen_load(void);
void title_screen_input(void);
void title_screen_update(void);
void title_screen_render(void);
byte title_screen_run(void);
void title_screen_unload(void);

scene_t* title_screen_get_scene(void);

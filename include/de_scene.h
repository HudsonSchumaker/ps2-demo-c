/**
* @file scene.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
    void (*load)(void);    // Load the scene
    void (*input)(void);   // Handle input
    void (*update)(void);  // Update the scene
    void (*render)(void);  // Render the scene
	byte (*run)(void);     // Game Loop for the scene
    void (*unload)(void);  // Unload the scene
} scene_t;

void scene_manager_load_screen(void);
byte scene_manager_set_scene(scene_t* scene);
float scene_manager_get_delta_time(void);
float scene_manager_calculate_delta_time(void);

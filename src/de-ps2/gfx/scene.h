/**
 * @file scene.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_SCENE_H
#define DE_SCENE_H

#include "../de.h"
#include "../gfx/color.h"
#include "../core/camera.h"
#include "../core/context.h"

typedef struct scene_t {
    void (*load)(void);   // Load the scene
    void (*input)(void);  // Handle input
    void (*update)(void); // Update the scene
    void (*render)(void); // Render the scene
	byte (*run)(void);    // Game Loop for the scene
    void (*unload)(void); // Unload the scene
    camera_t camera;      // Camera associated with the scene
} scene_t;

scene_t* scene_init(void);
void scene_quit(scene_t* scene);
byte scene_set_scene(scene_t* scene);

void scene_begin_render(void);
void scene_end_render(void);

bool scene_is_running(void);
void scene_set_running(bool running);

#endif /* DE_SCENE_H */

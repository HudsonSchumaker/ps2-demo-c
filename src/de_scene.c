/**
* @file scene.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_scene.h"

static float delta_time = 0.0f;
static scene_t* current_scene = NULL;

byte scene_manager_set_scene(scene_t* scene) {
    byte status = 0;
    if (current_scene && current_scene->unload) {
        current_scene->unload(); // unload the current scene
        //free(current_scene);
    }

    current_scene = scene;
    if (current_scene && current_scene->load) {
        current_scene->load();         // load the new scene
    }
    if (current_scene && current_scene->run) {
        status = current_scene->run(); // run the scene loop
    }
    return status;
}

float scene_manager_get_delta_time(void) {
    return delta_time;
}

float scene_manager_calculate_delta_time(void) {
    static Uint32 millisecs_previous_frame = 0;

    // Initialize on first call
    if (millisecs_previous_frame == 0) {
        millisecs_previous_frame = SDL_GetTicks();
        return 0.0f; // Return 0 for first frame
    }

    Uint32 current_ticks = SDL_GetTicks();
    Uint32 frame_time = current_ticks - millisecs_previous_frame;

    // Calculate delta time BEFORE applying frame rate limiting
    delta_time = frame_time / 1000.0f;

    // Cap delta time to prevent large jumps (e.g., when debugging)
    if (delta_time > 0.05f) { // Cap at 50ms (20 FPS minimum)
        delta_time = 0.05f;
    }

    // PS2 50 FPS frame limiting (20ms per frame)
    const Uint32 PS2_FRAME_TARGET = 20; // 20ms for 50 FPS
    if (frame_time < PS2_FRAME_TARGET) {
        SDL_Delay(PS2_FRAME_TARGET - frame_time);
    }

    millisecs_previous_frame = current_ticks;
    return delta_time;
}

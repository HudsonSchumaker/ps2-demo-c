/**
 * @file app.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "app.h"

void app_start(void) {
    byte next_scene = SCENE_SPLASH;
    scene_t* scene = NULL;
    engine_init();

    while (next_scene != SCENE_EXIT) {
        switch (next_scene) {
            case SCENE_SPLASH:
                splash_screen_init();
                scene = splash_screen_get_scene();
                break;

            case SCENE_TITLE:
                title_screen_init();
                scene = title_screen_get_scene();
                break;

            default:
                scene = NULL;
                next_scene = SCENE_EXIT;
                break;
        }

        if (scene == NULL) {
            break;
        }
        next_scene = scene_set_scene(scene);
    }
    scene_set_scene(NULL);
    engine_quit();
}

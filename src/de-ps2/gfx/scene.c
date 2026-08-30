/**
 * @file scene.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "scene.h"

static scene_t* current_scene = NULL;
static bool is_running = false;

static void scene_load_screen(void) {
    SDL_Renderer* renderer = ctx_get_renderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

scene_t* scene_init(void) {
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene) {
        return NULL;
    }
    scene->camera = camera_create(color_black());
    return scene;
}

void scene_quit(scene_t* scene) {
	if (scene) {
		free(scene);
	}
}

byte scene_set_scene(scene_t* scene) {
    byte status = 0;
    if (current_scene != NULL) {
        current_scene->unload();
    }

    current_scene = scene;
    if (current_scene != NULL) {
        scene_load_screen();
        current_scene->load();
        status = current_scene->run();
    }

    return status;
}

void scene_begin_render(void) {
    SDL_Renderer* renderer = ctx_get_renderer();
    SDL_SetRenderDrawColor(
        renderer,
        current_scene->camera.background_color.r,
        current_scene->camera.background_color.g,  
        current_scene->camera.background_color.b, 
        current_scene->camera.background_color.a
    );
    SDL_RenderClear(renderer);
}

void scene_end_render(void) {
    SDL_Renderer* renderer = ctx_get_renderer();
    SDL_RenderPresent(renderer);
}

bool scene_is_running(void) {
	return is_running;
}

void scene_set_running(bool running) {
	is_running = running;
}

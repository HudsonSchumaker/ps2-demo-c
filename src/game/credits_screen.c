/**
 * @file credits_screen.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "credits_screen.h"
static scene_t* credits_screen = NULL;
static label_t hudson_schumaker;
static path_t font_24_path[] = "cdrom0:/DATA/ALAGARD.TTF;1";
static path_t ok_sound_path[] = "cdrom0:/DATA/OK.WAV;1";

void credits_screen_init(void) {
    credits_screen = scene_init();
    credits_screen->load = credits_screen_load;
    credits_screen->input = credits_screen_input;
    credits_screen->update = credits_screen_update;
    credits_screen->render = credits_screen_render;
    credits_screen->run = credits_screen_run;
    credits_screen->unload = credits_screen_unload;
    printf("OK: credits_screen init.\n");
}

void credits_screen_load(void) {
    hudson_schumaker = write_create_text_cached(font_24_path, "Hudson Schumaker", 24, (color_t){255, 255, 255, 255});
    hudson_schumaker.position.x = (SCREEN_WIDTH - hudson_schumaker.size.w) / 2;
    hudson_schumaker.position.y = (SCREEN_HEIGHT - hudson_schumaker.size.h) / 2;

    scene_set_running(true);
    printf("OK: credits_screen load.\n");
}

void credits_screen_input(void) {
    if (input_is_button_pressed(SDL_CONTROLLER_BUTTON_START)) {
        scene_set_running(false); // ends run()'s loop, falls through to unload()
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            scene_set_running(false);
        }
    }
}

void credits_screen_update(void) {
    engine_calculate_delta_time();
}

void credits_screen_render(void) {
    scene_begin_render();
    {
        write_render_text(hudson_schumaker);
    }
    scene_end_render();
}

byte credits_screen_run(void) {
    sfx_play_sound_cached(ok_sound_path);
    while (scene_is_running()) {
        credits_screen_input();
        credits_screen_update();
        credits_screen_render();
    }
    return SCENE_SPLASH;
}

void credits_screen_unload(void) {
    write_destroy_text(hudson_schumaker);
    scene_set_running(false);
    printf("OK: credits_screen unload.\n");
}

scene_t* credits_screen_get_scene(void) {
    return credits_screen;
}

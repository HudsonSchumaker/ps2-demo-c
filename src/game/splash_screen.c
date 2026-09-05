/**
* @file splash_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "splash_screen.h"
static scene_t* splash_screen = NULL;
static texture_t logo_texture;
static texture_t dd_engine_texture;
static texture_t st_studios_texture;
static path_t logo_path[] = "cdrom0:/DATA/LOGO.PNG;1";
static path_t dd_engine_path[] = "cdrom0:/DATA/DD.PNG;1";
static path_t st_studios_path[] = "cdrom0:/DATA/ST.PNG;1";
static path_t font_path[] = "cdrom0:/DATA/ALAGARD.TTF;1";

void splash_screen_init(void) {
    splash_screen = scene_init();
    splash_screen->load   = splash_screen_load;
    splash_screen->input  = splash_screen_input;
    splash_screen->update = splash_screen_update;
    splash_screen->render = splash_screen_render;
    splash_screen->run    = splash_screen_run;
    splash_screen->unload = splash_screen_unload;
    printf("OK: splash_screen init.\n");
}

void splash_screen_load(void) {
    logo_texture = gfx_load_texture_cached(logo_path);
    logo_texture.position.x = (SCREEN_WIDTH - logo_texture.size.w) / 2;
    logo_texture.position.y = (SCREEN_HEIGHT - logo_texture.size.h) / 2;

    dd_engine_texture = gfx_load_texture_cached(dd_engine_path);
    dd_engine_texture.size.w = 32;
    dd_engine_texture.size.h = 32;
    dd_engine_texture.position.x = 0;
    dd_engine_texture.position.y = SCREEN_HEIGHT - dd_engine_texture.size.h;

    st_studios_texture = gfx_load_texture_cached(st_studios_path);
    st_studios_texture.size.w = 32;
    st_studios_texture.size.h = 32;
    st_studios_texture.position.x = dd_engine_texture.size.w + 2;
    st_studios_texture.position.y = SCREEN_HEIGHT - st_studios_texture.size.h;

    write_cache_font(font_path, 18);
    write_cache_font(font_path, 24);

    scene_set_running(true);
    printf("OK: splash_screen load.\n");
}

void splash_screen_input(void) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            scene_set_running(false);
        }
    }
}

void splash_screen_update(void) {
    static float timer = 0.0f;
    timer += engine_calculate_delta_time();

    if (timer > 2.99f) {
        timer = 0.0f;
        scene_set_running(false);
    }
}

void splash_screen_render(void) {
    scene_begin_render();
    {
        gfx_render_texture(logo_texture);
        gfx_render_texture(dd_engine_texture);
        gfx_render_texture(st_studios_texture);
    }
    scene_end_render();
}

byte splash_screen_run(void) {
    while (scene_is_running()) {
        splash_screen_input();
        splash_screen_update();
        splash_screen_render();
    }
    return SCENE_TITLE;
}

void splash_screen_unload(void) {
    scene_set_running(false);
    printf("OK: splash_screen unload.\n");
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}

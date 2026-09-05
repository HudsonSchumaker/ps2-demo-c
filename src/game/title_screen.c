/**
 * @file title_screen.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "title_screen.h"
static scene_t *title_screen = NULL;
static texture_t btn_r1;
static texture_t btn_l1;
static texture_t btn_cross;
static texture_t btn_circle;
static texture_t btn_square;
static texture_t btn_triangle;
static path_t btn_r1_path[] = "cdrom0:/DATA/R1.PNG;1";
static path_t btn_l1_path[] = "cdrom0:/DATA/L1.PNG;1";
static path_t btn_cross_path[] = "cdrom0:/DATA/CROSS.PNG;1";
static path_t btn_circle_path[] = "cdrom0:/DATA/CIRCLE.PNG;1";
static path_t btn_square_path[] = "cdrom0:/DATA/SQUARE.PNG;1";
static path_t btn_triangle_path[] = "cdrom0:/DATA/TRIANGLE.PNG;1";

static texture_t enter;
static path_t enter_path[] = "cdrom0:/DATA/ENTER.PNG;1";
static path_t ok_sound_path[] = "cdrom0:/DATA/OK.WAV;1";
static path_t puzzle_music_path[] = "cdrom0:/DATA/PUZZLE.OGG;1";

void title_screen_init(void) {
    title_screen = scene_init();
    title_screen->load = title_screen_load;
    title_screen->input = title_screen_input;
    title_screen->update = title_screen_update;
    title_screen->render = title_screen_render;
    title_screen->run = title_screen_run;
    title_screen->unload = title_screen_unload;
    printf("OK: title_screen init.\n");
}

void title_screen_load(void) {
    sfx_cache_sound(ok_sound_path);
    sfx_cache_music(puzzle_music_path);

    btn_r1 = gfx_load_texture_cached(btn_r1_path);
    btn_r1.position.x = 50;
    btn_r1.position.y = 100;
    btn_l1 = gfx_load_texture_cached(btn_l1_path);
    btn_l1.position.x = 100;
    btn_l1.position.y = 100;
    btn_cross = gfx_load_texture_cached(btn_cross_path);
    btn_cross.position.x = 150;
    btn_cross.position.y = 100;
    btn_circle = gfx_load_texture_cached(btn_circle_path);
    btn_circle.position.x = 200;
    btn_circle.position.y = 100;
    btn_triangle = gfx_load_texture_cached(btn_triangle_path);
    btn_triangle.position.x = 300;
    btn_triangle.position.y = 100;
    btn_square = gfx_load_texture_cached(btn_square_path);
    btn_square.position.x = 250;
    btn_square.position.y = 100;

    enter = gfx_load_texture_cached(enter_path);
    scene_set_running(true);
    printf("OK: title_screen load.\n");
}

void title_screen_input(void) {
    SDL_GameController *controller = input_get_controller();
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) {
        scene_set_running(false);
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            scene_set_running(false);
        }
    }
}

void title_screen_update(void) {
    engine_calculate_delta_time();
}

void title_screen_render(void) {
    static short speed = 8;
    SDL_Renderer* renderer = ctx_get_renderer();

    scene_begin_render();
    {
        gfx_render_texture(btn_r1);
        gfx_render_texture(btn_l1);
        gfx_render_texture(btn_cross);
        gfx_render_texture(btn_circle);
        gfx_render_texture(btn_square);
        gfx_render_texture(btn_triangle);

        SDL_Rect rect = {
            100,
            300 + (int)(speed * SDL_sin(SDL_GetTicks() * (PI_F / 1600.0f))),
            enter.size.w,
            enter.size.h};
        SDL_RenderCopy(renderer, enter.texture, NULL, &rect);
    }
    scene_end_render();
}

byte title_screen_run(void) {
    sfx_play_music_cached(puzzle_music_path);

    while (scene_is_running()) {
        title_screen_input();
        title_screen_update();
        title_screen_render();
    }
    return SCENE_CREDITS;
}

void title_screen_unload(void) {
    sfx_stop_all();

    scene_set_running(false);
    printf("OK: title_screen unload\n");
    printf("Texture cache count: %d\n", gfx_get_texture_cache_count());
    printf("Font cache count: %d\n", write_get_font_cache_count());
    printf("Sound cache count: %d\n", sfx_get_sound_cache_count());
    printf("Music cache count: %d\n", sfx_get_music_cache_count());
}

scene_t *title_screen_get_scene(void) {
    return title_screen;
}

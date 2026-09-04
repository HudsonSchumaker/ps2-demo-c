/**
* @file title_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "title_screen.h"
static scene_t* title_screen = NULL;
static texture_t bg_texture;
static texture_t spc_bar_texture;
static label_t text;

static path_t bg_path[] = "cdrom0:/DATA/BG1.PNG;1";
static path_t font_path[] = "cdrom0:/DATA/ALAGARD.TTF;1";
static path_t spc_bar_path[] = "cdrom0:/DATA/SPCBAR.PNG;1";

static path_t ok_sound_path[] = "cdrom0:/DATA/OK.WAV;1";
static path_t puzzle_music_path[] = "cdrom0:/DATA/PUZZLE.OGG;1";

void title_screen_init(void) {
    title_screen = scene_init();

    title_screen->load   = title_screen_load;
    title_screen->input  = title_screen_input;
    title_screen->update = title_screen_update;
    title_screen->render = title_screen_render;
    title_screen->run    = title_screen_run;
    title_screen->unload = title_screen_unload;
    printf("OK: title_screen init.\n");
}

void title_screen_load(void) {
    bg_texture = gfx_load_texture_cached(bg_path);
    spc_bar_texture = gfx_load_texture_cached(spc_bar_path);
   
    text = write_create_text_cached(font_path, "PRESS START", 18, (color_t){255, 0, 0, 255});
    text.position.x = (SCREEN_WIDTH - text.size.w) / 2;
    text.position.y = SCREEN_HEIGHT - 120;

    sfx_cache_sound(ok_sound_path);
    sfx_cache_music(puzzle_music_path);

    scene_set_running(true);
    printf("OK: title_screen load.\n");
}

void title_screen_input(void) {
    SDL_GameController* controller = input_get_controller();
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
		scene_set_running(false);
	}

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                scene_set_running(false);
                break;
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
        SDL_Rect bg_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, bg_texture.texture, NULL, &bg_rect);

        SDL_Rect rect = {
            100,
            300 + (int)(speed * SDL_sin(SDL_GetTicks() * (PI_F / 1600.0f))),
            spc_bar_texture.size.w,
            spc_bar_texture.size.h
        };
        SDL_RenderCopy(renderer, spc_bar_texture.texture, NULL, &rect);

        write_render_text(text);
    }
    scene_end_render();
}

byte title_screen_run(void) {
    sfx_play_sound_cached(ok_sound_path);
    sfx_play_music_cached(puzzle_music_path);

    while (scene_is_running()) {
        title_screen_input();
        title_screen_update();
        title_screen_render();
    }
    return SCENE_SPLASH;
}

void title_screen_unload(void) {
    sfx_stop_all();
    write_destroy_text(text);

    scene_set_running(false);
    printf("OK: title_screen unload\n");
    printf("Texture cache count: %d\n", gfx_get_texture_cache_count());
    printf("Font cache count: %d\n", write_get_font_cache_count());
    printf("Sound cache count: %d\n", sfx_get_sound_cache_count());
    printf("Music cache count: %d\n", sfx_get_music_cache_count());
}

scene_t* title_screen_get_scene(void) {
    return title_screen;
}

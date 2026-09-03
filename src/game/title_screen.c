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

void title_screen_init(void) {
    title_screen = malloc(sizeof(scene_t));
    if (title_screen == NULL) {
        printf("ERROR: allocate memory for title screen failed.\n");
        exit(EXIT_FAILURE);
    }

    title_screen->load   = title_screen_load;
    title_screen->input  = title_screen_input;
    title_screen->update = title_screen_update;
    title_screen->render = title_screen_render;
    title_screen->run    = title_screen_run;
    title_screen->unload = title_screen_unload;
    printf("OK: title_screen init.\n");
}

void title_screen_load(void) {
    char bg_path[] = "cdrom0:\\DATA\\BG1.PNG;1";
    bg_texture = load_texture_t(bg_path);
    spc_bar_texture = load_texture_t("cdrom0:\\DATA\\SPCBAR.PNG;1");
   
    text = write_create_text("cdrom0:\\DATA\\ALAGARD.TTF;1", "PRESS START", 18, (color_t){255, 0, 0, 255});

    sfx_load_sound("cdrom0:\\DATA\\OK.WAV;1");
    sfx_load_music("cdrom0:\\DATA\\PUZZLE.OGG;1");

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

        SDL_FRect text_dst = {
            (SCREEN_WIDTH - text.size.w) / 2,
            SCREEN_HEIGHT - 120,
            text.size.w,
            text.size.h
        };
        SDL_RenderCopyF(renderer, text.texture, NULL, &text_dst);
    }
    scene_end_render();
}

byte title_screen_run(void) {
    sfx_play_sound();
    sfx_play_music();

    while (scene_is_running()) {
        title_screen_input();
        title_screen_update();
        title_screen_render();
    }
    return NEXT;
}

void title_screen_unload(void) {
    unload_texture_t(bg_texture);
    unload_texture_t(spc_bar_texture);
    
    sfx_stop_sound();
    sfx_stop_music();

    scene_set_running(false);
    printf("OK: title_screen unload\n");
}

scene_t* title_screen_get_scene(void) {
    return title_screen;
}

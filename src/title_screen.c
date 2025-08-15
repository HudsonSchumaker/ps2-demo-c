/**
* @file title_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/title_screen.h"
#include "../include/de_gfx.h"
#include "../include/de_sfx.h"
#include "../include/de_input.h"

static bool running = false;
static scene_t* title_screen = NULL;

static SDL_Renderer* renderer = NULL;
static SDL_Texture* bgTexture = NULL;
static SDL_Rect bgRect;

void title_screen_init(void) {
    title_screen = (scene_t*)malloc(sizeof(scene_t));
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
}

void title_screen_load(void) {
    renderer = gfx_get_renderer();

    char bg_path[] = "cdrom0:\\DATA\\BG512.PNG;1";
    bgTexture = gfx_load_texture(bg_path);

    bgRect = gfx_get_texture_rect(bgTexture);
    bgRect.x = (SCREEN_WIDTH - bgRect.w) / 2;
    bgRect.y = (SCREEN_HEIGHT - bgRect.h) / 2;
    bgRect.w = SCREEN_WIDTH;
    bgRect.h = SCREEN_HEIGHT;

    sfx_load_sound("cdrom0:\\DATA\\OK.WAV;1");
    sfx_load_music("cdrom0:\\DATA\\INTRO.MP3;1");

    running = true;
}

void title_screen_input(void) {
    SDL_GameController* controller = input_get_controller();
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
		running = false;
	}

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                running = false;
                break;
        }
    }
}

void title_screen_update(void) {
    scene_manager_calculate_delta_time();
}

void title_screen_render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
    SDL_RenderPresent(renderer);
}

byte title_screen_run(void) {
    sfx_play_sound();
    sfx_play_music();

    while (running) {
        title_screen_input();
        title_screen_update();
        title_screen_render();
    }
    return NEXT;
}

void title_screen_unload(void) {
    renderer = NULL;
    if (bgTexture) {
        SDL_DestroyTexture(bgTexture);
        bgTexture = NULL;
    }

    sfx_stop_sound();
    sfx_stop_music();

    printf("Title Screen: Unload\n");
}

scene_t* title_screen_get_scene(void) {
    return title_screen;
}

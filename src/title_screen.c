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

static SDL_Texture* bg_texture = NULL;
static SDL_Rect bg_rect;
static SDL_Texture* spc_bar_texture = NULL;
static SDL_Rect spc_bar_rect;

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

    char bg_path[] = "cdrom0:\\DATA\\BG1.PNG;1";
    bg_texture = gfx_load_texture(bg_path);

    bg_rect = gfx_get_texture_rect(bg_texture);
    bg_rect.x = 0;
    bg_rect.y = 0;
    bg_rect.w = SCREEN_WIDTH;
    bg_rect.h = SCREEN_HEIGHT;

    spc_bar_texture = gfx_load_texture("cdrom0:\\DATA\\SPCBAR.PNG;1");
    spc_bar_rect = gfx_get_texture_rect(spc_bar_texture);
   
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
    static short speed = 8;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bg_texture, NULL, &bg_rect);

    SDL_Rect rect = {
        100,
        200 + (int)(speed * SDL_sin(SDL_GetTicks() * (PI / 1600.0f))),
        spc_bar_rect.w,
        spc_bar_rect.h
    };
	SDL_RenderCopy(renderer, spc_bar_texture, NULL, &rect);

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
    if (bg_texture) {
        SDL_DestroyTexture(bg_texture);
        bg_texture = NULL;
    }

    if (spc_bar_texture) {
        SDL_DestroyTexture(spc_bar_texture);
        spc_bar_texture = NULL;
    }

    sfx_stop_sound();
    sfx_stop_music();

    printf("OK: title_screen unload\n");
}

scene_t* title_screen_get_scene(void) {
    return title_screen;
}

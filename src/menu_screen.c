/**
* @file menu_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/menu_screen.h"
#include "../include/de_gfx.h"
#include "../include/de_sfx.h"
#include "../include/de_input.h"

static bool running = false;
static scene_t* menu_screen = NULL;

static SDL_Rect bg_rect;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* bg_texture = NULL;

void menu_screen_init(void) {
    menu_screen = (scene_t*)malloc(sizeof(scene_t));
    if (menu_screen == NULL) {
        printf("ERROR: allocate memory for menu_screen failed.\n");
        exit(EXIT_FAILURE);
    }

    menu_screen->load   = menu_screen_load;
    menu_screen->input  = menu_screen_input;
    menu_screen->update = menu_screen_update;
    menu_screen->render = menu_screen_render;
    menu_screen->run    = menu_screen_run;
    menu_screen->unload = menu_screen_unload;
}

void menu_screen_load(void) {
    renderer = gfx_get_renderer();

    char bg_path[] = "cdrom0:\\DATA\\TSMBS.JPG;1";
    bg_texture = gfx_load_texture(bg_path);

    bg_rect = gfx_get_texture_rect(bg_texture);
    bg_rect.x = 0;
    bg_rect.y = 0;
    bg_rect.w = SCREEN_WIDTH;
    bg_rect.h = SCREEN_HEIGHT;

    running = true;

    printf("OK: menu_screen load\n");
}

void menu_screen_input(void) {
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

void menu_screen_update(void) {
    scene_manager_calculate_delta_time();
}

void menu_screen_render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bg_texture, NULL, &bg_rect);

    SDL_RenderPresent(renderer);
}

byte menu_screen_run(void) {
    sfx_play_sound();
    sfx_play_music();

    while (running) {
        menu_screen_input();
        menu_screen_update();
        menu_screen_render();
    }
    return NEXT;
}

void menu_screen_unload(void) {
    renderer = NULL;
    if (bg_texture) {
        SDL_DestroyTexture(bg_texture);
        bg_texture = NULL;
    }

    sfx_stop_sound();
    sfx_stop_music();

    printf("OK: menu_screen unload\n");
}

scene_t* menu_screen_get_scene(void) {
    return menu_screen;
}

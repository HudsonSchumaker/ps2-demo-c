/**
* @file splash_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/splash_screen.h"
#include "../include/de_gfx.h"
#include "../include/de_sfx.h"
#include "../include/de_input.h"
#include "../include/de_camera.h"

static bool running = false;
static scene_t* splash_screen = NULL;

static SDL_Renderer* renderer = NULL;
static SDL_Texture* logoTexture = NULL;
static SDL_Rect logoRect;

void splash_screen_init(void) {
    splash_screen = (scene_t*)malloc(sizeof(scene_t));
    if (splash_screen == NULL) {
        printf("ERROR: allocate memory for splashscreen failed.\n");
        exit(EXIT_FAILURE);
    }

    splash_screen->load   = splash_screen_load;
    splash_screen->input  = splash_screen_input;
    splash_screen->update = splash_screen_update;
    splash_screen->render = splash_screen_render;
    splash_screen->run    = splash_screen_run;
    splash_screen->unload = splash_screen_unload;

    printf("Splash Screen: Init\n");
}

void splash_screen_load(void) {
    renderer = gfx_get_renderer();

    char path[] = "cdrom0:\\DATA\\LOGO.PNG;1";
    logoTexture = gfx_load_texture(path);

    logoRect = gfx_get_texture_rect(logoTexture);
    logoRect.x = (SCREEN_WIDTH - logoRect.w) / 2;
    logoRect.y = (SCREEN_HEIGHT - logoRect.h) / 2;
    logoRect.w = 256;
    logoRect.h = 64;

    sfx_load_sound("cdrom0:\\DATA\\OK.WAV");
    sfx_load_music("cdrom0:\\DATA\\INTRO.MP3");

    running = true;
    printf("Splash Screen: Load\n");
}

void splash_screen_input(void) {
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

void splash_screen_update(void) {
    scene_manager_calculate_delta_time();
}

void splash_screen_render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
    SDL_RenderPresent(renderer);
}

short splash_screen_run(void) {
    sfx_play_sound();
    sfx_play_music();
    
    while (running) {
        splash_screen_input();
        splash_screen_update();
        splash_screen_render();
    }
    return NEXT;
}

void splash_screen_unload(void) {
    renderer = NULL;
    if (logoTexture) {
        SDL_DestroyTexture(logoTexture);
        logoTexture = NULL;
    }

    sfx

    printf("Splash Screen: Unload\n");
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}

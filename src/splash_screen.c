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

static bool running = false;
static scene_t* splash_screen = NULL;

static SDL_Rect logo_rect;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* logo_texture = NULL;

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
    printf("OK: splash_screen init\n");
}

void splash_screen_load(void) {
    renderer = gfx_get_renderer();

    char logo_path[] = "cdrom0:\\DATA\\LOGO.PNG;1";
    logo_texture = gfx_load_texture(logo_path);
    
    logo_rect = gfx_get_texture_rect(logo_texture);
    logo_rect.x = (SCREEN_WIDTH - logo_rect.w) / 2;
    logo_rect.y = (SCREEN_HEIGHT - logo_rect.h) / 2;
    logo_rect.w = 256;
    logo_rect.h = 64;

    sfx_load_sound("cdrom0:\\DATA\\OK.WAV;1");
    running = true;

    printf("OK: splash_screen load\n");
}

void splash_screen_input(void) {
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
    static char times = 0;
    SDL_Delay(1000);
    times++;
    if (times > 6) {
        running = false;
    }
}

void splash_screen_render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, logo_texture, NULL, &logo_rect);
    SDL_RenderPresent(renderer);
}

byte splash_screen_run(void) {
    while (running) {
        splash_screen_input();
        splash_screen_update();
        splash_screen_render();
    }
    return NEXT;
}

void splash_screen_unload(void) {
    renderer = NULL;
    if (logo_texture) {
        SDL_DestroyTexture(logo_texture);
        logo_texture = NULL;
    }

    printf("OK: splash_screen unload\n");
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}

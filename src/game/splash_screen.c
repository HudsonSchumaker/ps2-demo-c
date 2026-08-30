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
static rect_t logo_rect = {0};

void splash_screen_init(void) {
    splash_screen = malloc(sizeof(scene_t));
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
    printf("OK: splash_screen init.\n");
}

void splash_screen_load(void) {
    char logo_path[] = "cdrom0:\\DATA\\LOGO.PNG;1";
    logo_texture = load_texture_t(logo_path);
    
    logo_rect.w = logo_texture.size.w;
    logo_rect.h = logo_texture.size.h;
    
    logo_rect.x = (SCREEN_WIDTH - logo_rect.w) / 2;
    logo_rect.y = (SCREEN_HEIGHT - logo_rect.h) / 2;

    scene_set_running(true);
    printf("OK: splash_screen load.\n");
}

void splash_screen_input(void) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                scene_set_running(false);
                break;
        }
    }
}

void splash_screen_update(void) {
    static char times = 0;
    SDL_Delay(1000);
    times++;
    if (times > 6) {
        scene_set_running(false);
    }
}

void splash_screen_render(void) {
    SDL_Renderer* renderer = ctx_get_renderer();
    scene_begin_render();
    {
        SDL_Rect dst = { logo_rect.x, logo_rect.y, logo_rect.w, logo_rect.h };
        SDL_RenderCopy(renderer, logo_texture.texture, NULL, &dst);
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
    unload_texture_t(logo_texture);
    scene_set_running(false);
    printf("OK: splash_screen unload.\n");
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}

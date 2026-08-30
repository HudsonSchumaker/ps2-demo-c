/**
 * @file context.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "context.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

bool ctx_init(void) {
    SDL_SetHint(SDL_HINT_PS2_GS_MODE, "PAL");
    SDL_SetHint(SDL_HINT_PS2_GS_WIDTH, "640");
    SDL_SetHint(SDL_HINT_PS2_GS_HEIGHT, "512");
    SDL_SetHint(SDL_HINT_PS2_GS_PROGRESSIVE, "0");
    SDL_SetHint(SDL_HINT_PS2_DYNAMIC_VSYNC, "1");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return false;
    }
    
    window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        SDL_Quit();
        return false;
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (TTF_Init() != 0) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    sfx_init();
    input_init();
    return true;
}

void ctx_quit(void) {
    Mix_HaltChannel(-1);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_Quit();
}

SDL_Window* ctx_get_window(void) {
    return window;
}

SDL_Renderer* ctx_get_renderer(void) {
    return renderer;
}

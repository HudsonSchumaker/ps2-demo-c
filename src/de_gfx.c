/**
* @file gfx.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_gfx.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

void gfx_init(void) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: SDL2 initialization failed: %s\n", SDL_GetError());
        return;
    }

    // Create window (PS2 resolution)
    window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, // PS2 resolution
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("ERROR: Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("ERROR: Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("ERROR: SDL_image initialization failed: %s\n", IMG_GetError());
        return;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("ERROR: SDL_ttf initialization failed: %s\n", TTF_GetError());
        return;
    }
}

SDL_Window* gfx_get_window(void) {
    return window;
}

SDL_Renderer* gfx_get_renderer(void) {
    return renderer;
}

SDL_Texture* gfx_load_texture(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        printf("ERROR: fopen failed!\n");
        return NULL;
    }

    SDL_RWops* rw = SDL_RWFromFP(file, SDL_TRUE); // SDL_TRUE = auto close
    if (!rw) {
        printf("ERROR: SDL_RWFromFP failed!\n");
        fclose(file);
        return NULL;
    }

    SDL_Surface* surface = IMG_Load_RW(rw, 1); // 1 = auto free rw
    if (!surface) {
        printf("ERROR: IMG_Load_RW failed: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Surface* ps2_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB565, 0);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, ps2_surface);
    
    SDL_FreeSurface(surface);
    SDL_FreeSurface(ps2_surface);
    return texture;
}

SDL_Rect gfx_get_texture_rect(SDL_Texture* texture) {
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = 0;
    rect.y = 0;
    return rect;
}

void gfx_close(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

/**
* @file main.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_gfx.h"
#include "../include/de_sfx.h"
#include "../include/de_input.h"

void setUp(void) {
    // Initialize PS2 systems
    SifInitRpc(0);

    gfx_init();
    sfx_init();
    input_init();
}

void init(void) {
    setUp();
}

int main(int argc, char *argv[]) {
    init();
    bool isRunning = true;
    SDL_Renderer* renderer = gfx_get_renderer();

    char path[] = "cdrom0:\\DATA\\LOGO.PNG;1";
    SDL_Texture* logoTexture = gfx_load_texture(path);
    
    SDL_Rect logoRect = gfx_get_texture_rect(logoTexture);
    logoRect.x = (SCREEN_WIDTH - logoRect.w) / 2;
    logoRect.y = (SCREEN_HEIGHT - logoRect.h) / 2;
    logoRect.w = 256;
    logoRect.h = 64;

    sfx_load_sound("cdrom0:\\DATA\\OK.WAV");
    sfx_load_music("cdrom0:\\DATA\\INTRO.MP3");

    sfx_play_sound();
    sfx_play_music();

    while (isRunning) {
        SDL_GameController* controller = input_get_controller();
	    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
	    	isRunning = false;
	    }

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
        SDL_RenderPresent(renderer);

        SDL_Delay(FRAME_TARGET_TIME); // ~60 FPS
    }

    input_close();
    sfx_close();
    gfx_close();

    return 0;
}

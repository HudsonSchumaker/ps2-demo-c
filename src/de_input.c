/**
* @file input.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_input.h"
static SDL_GameController* controller = NULL;

void input_init(void) {
    // Initialize SDL game controller
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0) {
        printf("ERROR: SDL_InitSubSystem failed: %s\n", SDL_GetError());
        return;
    }

    controller = SDL_GameControllerOpen(0);
    if (!controller) {
        printf("ERROR: SDL_GameControllerOpen failed: %s\n", SDL_GetError());
    }
}

SDL_GameController* input_get_controller(void) {
    return controller;
}

void input_close(void) {
    if (controller) {
        SDL_GameControllerClose(controller);
        controller = NULL;
    }
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC);
}

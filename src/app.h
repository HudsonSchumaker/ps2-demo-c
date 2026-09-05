/**
 * @file app.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_APP_H
#define DE_APP_H

#include "de-ps2/de.h"
#include "de-ps2/core/engine.h"
#include "game/title_screen.h"
#include "game/splash_screen.h"
#include "game/credits_screen.h"

typedef enum scene_id_e {
    SCENE_EXIT = 0,
    SCENE_SPLASH,
    SCENE_TITLE,
    SCENE_MENU,
    SCENE_GAME,
    SCENE_CREDITS
} scene_id_e;

/**
 * @brief Starts the application by initializing the engine, running the splash screen,
 * title screen, menu screen, and credits screen, and then quitting the engine.
*/
void app_start(void);

#endif /* DE_APP_H */

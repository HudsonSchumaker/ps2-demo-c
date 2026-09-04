/**
 * @file input.h
 * @author Hudson Schumaker
 * @brief Implements the core input functions, including initialization and quitting.
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2025, Dodoi-Lab
 */
#ifndef INPUT_H
#define INPUT_H

#include "../de.h"

void input_init(void);
void input_quit(void);

SDL_GameController* input_get_controller(void);

#endif /* INPUT_H */

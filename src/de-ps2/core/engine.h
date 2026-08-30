/**
 * @file engine.h
 * @author Hudson Schumaker
 * @brief Implements the core engine functions, including initialization, quitting, and delta time calculation.
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#ifndef DE_ENGINE_H
#define DE_ENGINE_H

#include "../de.h"
#include "context.h"

#define MAX_DT 0.25f
#define SMOOTH_ALPHA 0.08f

void engine_init(void);
void engine_quit(void);

float engine_get_delta_time(void);
float engine_calculate_delta_time(void);

#endif /* DE_ENGINE_H */

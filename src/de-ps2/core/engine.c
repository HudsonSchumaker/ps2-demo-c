/**
 * @file engine.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "engine.h"
static float delta_time = 0.0f;

void engine_init(void) {
    SifInitRpc(0);
    srand((unsigned int)time(NULL));
    if (!ctx_init()) {
        exit(EXIT_FAILURE);
    }
}

void engine_quit(void) {
    ctx_quit();
}

float engine_get_delta_time(void) {
    return delta_time;
}

float engine_calculate_delta_time(void) {
    static unsigned long long frequency = 0;
    static unsigned long long last_counter = 0;
    static float smooth_dt = 0.0f;

    if (frequency == 0) {
        frequency = SDL_GetPerformanceFrequency();
    }
    unsigned long long now = SDL_GetPerformanceCounter();

    if (last_counter == 0) {
        last_counter = now;
        return 0.0f;
    }

    float dt = (float)(now - last_counter) / (float)frequency;
    last_counter = now;

    if (dt < 0.0f) {
        dt = 0.0f;
    }

    if (dt > MAX_DT) {
        dt = MAX_DT;
    }

    if (smooth_dt == 0.0f) {
        smooth_dt = dt;
    } else {
        smooth_dt += SMOOTH_ALPHA * (dt - smooth_dt);
    }

    delta_time = smooth_dt;
    return delta_time;
}

/**
 * @file math2d.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "math2d.h"
static float sct_table[SIN_LUT_SIZE];

void build_trigo_tables(void) {
    for (int i = 0; i < SIN_LUT_SIZE; i++) {
        float angle =  ((float)i / SIN_LUT_SIZE) * TWO_PI_F;
        sct_table[i] = sinf(angle);
    }
}

int degrees_to_index(float degrees) {
    return (int)(degrees * TABLE_SCALE) & ANGLE_MASK;
}

float de_sinf(int angle) {
    return sct_table[angle & ANGLE_MASK];
}

float de_cosf(int angle) {
    return sct_table[(angle + (SIN_LUT_SIZE >> 2)) & ANGLE_MASK];
}

float de_tanf(int angle) {
    float cos = de_cosf(angle);
    if (cos > -0.0001f && cos < 0.0001f) {
        return 0.0f;
    }

    return de_sinf(angle) / cos;
}

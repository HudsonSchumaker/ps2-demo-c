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
#include "../include/splash_screen.h"

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

    splash_screen_init();
    scene_t* splash_screen = splash_screen_get_scene();
	short r = scene_manager_set_scene(splash_screen);
    

    input_close();
    sfx_close();
    gfx_close();

    return 0;
}

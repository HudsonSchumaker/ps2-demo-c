/**
* @file main.c
* @author Hudson Schumaker
* @version 1.0.0
*
* PS2 specs
* CPU: Emotion Engine 295 MHz (MIPS R5900)
* GPU: Graphics Synthesizer 147 MHz
* RAM: 32 MB
* VRAM: 4 MB
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_gfx.h"
#include "../include/de_sfx.h"
#include "../include/de_input.h"
#include "../include/menu_screen.h"
#include "../include/title_screen.h"
#include "../include/splash_screen.h"

void set_up(void) {
    // Initialize PS2 systems
    SifInitRpc(0);

    gfx_init();
    sfx_init();
    input_init();
}

void init(void) {
    set_up();
}

int main(int argc, char *argv[]) {
    init();

    splash_screen_init();
    scene_t* splash_screen = splash_screen_get_scene();
    short r = scene_manager_set_scene(splash_screen);

    title_screen_init();
    scene_t* title_screen = title_screen_get_scene();
    scene_manager_set_scene(title_screen);

    menu_screen_init();
    scene_t* menu_screen = menu_screen_get_scene();
    scene_manager_set_scene(menu_screen);

    input_close();
    sfx_close();
    gfx_close();
    return 0;
}

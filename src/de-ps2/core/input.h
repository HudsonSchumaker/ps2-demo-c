#ifndef INPUT_H
#define INPUT_H

#include "../de.h"

void input_init(void);
SDL_GameController* input_get_controller(void);
void input_close(void);

#endif /* INPUT_H */

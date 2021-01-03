#include "structures.h"

#ifndef INIT_H
#define INIT_H

SDL_Renderer *getrenderer(void);

void init(char *title);

void cleanup();

void loadGame(void);

#endif

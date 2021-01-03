#include "structures.h"

#ifndef DRAW_H
#define DRAW_H

void drawGame(void);

SDL_Texture *loadImage(char *name);

void drawImage(SDL_Texture *image, int x, int y);

void delay(unsigned int frameLimit);

void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);

#endif

#include "structures.h"

#ifndef MAP_H
#define MAP_H

void initMaps(void);

SDL_Texture *getBackground(void);

void loadMap(char *name);

void drawMap();

void changeLevel(void);

void cleanMaps(void);

GameObject *getPlayer(void);

int getPlayerx(void);

int getPlayery(void);

void setPlayerx(int valeur);

void setPlayery(int valeur);

int getLevel(void);

void initPlayerSprites(void);

void cleanPlayer(void);

void initializePlayer(void);

void drawPlayer(void);

void updatePlayer(Input *input);

#endif

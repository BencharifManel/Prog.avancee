#include "structures.h"

#ifndef PROTOTYPES
#define PROTOTYPES

#include "structures.h"

//On utilise extern car les fonctions peuvent se trouver dans n'importe quel fichier du projet
//extern void centerScrollingOnPlayer(void);
extern void changeLevel(Map *map);
extern void cleanMaps(Map *map);
extern void cleanPlayer(void);
extern void cleanup(Map *map);
extern void delay(unsigned int frameLimit);
extern void drawGame(Map *map, GameObject *player);
extern void drawImage(SDL_Texture *, int, int);
extern void drawMap(Map map);
extern void drawPlayer(GameObject *player);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern SDL_Texture *getBackground(Map map);
extern int getBeginX(void);
extern int getBeginY(void);
extern void getInput(Input *input);
extern int getLevel(void);
extern int getMaxX(void);
extern int getMaxY(void);
extern GameObject *getPlayer(GameObject player);
extern int getPlayerDirection(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern SDL_Renderer *getrenderer(void);
extern int getStartX(void);
extern int getStartY(void);
extern void init(char *title);
extern void initializePlayer(GameObject *player);
extern void initMaps(Map *map);
extern void initPlayerSprites();
extern void loadGame(Map *map);
extern SDL_Texture *loadImage(char *name);
extern void loadMap(char *name, Map map);
extern void setNombreDeVies(int valeur);
extern void setNombreDetoiles(int valeur);
extern void setStartX(int valeur);
extern void setStartY(int valeur);
extern void updatePlayer(Input *input,GameObject *player, Map *map);

#endif

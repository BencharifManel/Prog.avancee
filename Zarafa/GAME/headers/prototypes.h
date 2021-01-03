#include "structures.h"

#ifndef PROTOTYPES
#define PROTOTYPES

#include "structures.h"

//On utilise extern car les fonctions peuvent se trouver dans n'importe quel fichier du projet
//extern void centerScrollingOnPlayer(void);
extern void changeLevel(void);
extern void cleanMaps(void);
extern void cleanPlayer(void);
extern void cleanup(void);
extern void delay(unsigned int frameLimit);
extern void drawGame(void);
extern void drawImage(SDL_Texture *, int, int);
extern void drawMap();
extern void drawPlayer(void);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern SDL_Texture *getBackground(void);
extern int getBeginX(void);
extern int getBeginY(void);
extern void getInput(Input *input);
extern int getLevel(void);
extern int getMaxX(void);
extern int getMaxY(void);
extern GameObject *getPlayer(void);
extern int getPlayerDirection(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern SDL_Renderer *getrenderer(void);
extern int getStartX(void);
extern int getStartY(void);
extern void init(char *);
extern void initializePlayer(void);
extern void initMaps(void);
extern void initPlayerSprites(void);
extern void loadGame(void);
extern SDL_Texture *loadImage(char *name);
extern void loadMap(char *name);
extern void setNombreDeVies(int valeur);
extern void setNombreDetoiles(int valeur);
extern void setStartX(int valeur);
extern void setStartY(int valeur);
extern void updatePlayer(Input *input);
extern void drawScore(SDL_Renderer *renderer, GameObject *player,TTF_Font *font);
extern void drawTexte(TTF_Font *font, int x, int y, int w, int h, char *text);
extern TTF_Font *loadFont(char *name, int font_size);
extern int readScore(char *name);
extern void saveScore(char *name);
extern void drawMenu(void);

#endif

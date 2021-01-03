#include "prototypes.h"


Map map;


void initMaps(void){
    // Charge l'image du fond (background)
    map.background = loadImage("sprites/background.png");

    //On initialise le timer
    //map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
    //map.tileSetNumber = 0;
}


SDL_Texture *getBackground(void){
    return map.background;
}


void loadMap(char *name){
    //On ouvre le fichier et vérifie qu'il est non NULL
               FILE * pFile;
               int c;
               pFile=fopen (name,"r");
               if (pFile==NULL){
                 perror ("Error opening file");
               }
               //Si le fichier est non NULL
               else {
                  int i = 0; int j = 0;
                  do {
                    //On ouvre et parcourt le fichier
                    c = fgetc (pFile);
                    if ((c == '\n') || (c == '\r')){
                      if (c == '\n'){
                        i ++;
                        j = 0;
                      }
                    }
                    else{

                      map.tile[i][j] = c;
                      j ++;
                    }
                  } while (c != EOF);
                    fclose (pFile);
                  }
            }


void drawMap(){
                int dstx = 0;
                int dsty = 0;
                int srcx = 0;
                int srcy = 0;
              	for(int i = 0; i < 9; i++){
                    dstx = 0;
              		for(int j = 0; j < 13 ; j++){
              			if (map.tile[i][j] == '0'){
                            srcx = TILE_SIZE * 0;
                            drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                            dstx += TILE_SIZE;
                        }else if (map.tile[i][j] == '1'){
                            srcx = TILE_SIZE * 1;
                            drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                            dstx += TILE_SIZE;
                        }else if (map.tile[i][j] == '2'){
                            srcx = TILE_SIZE * 2;
                            drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                            dstx += TILE_SIZE;
                        }else if (map.tile[i][j] == '3'){
                            srcx = TILE_SIZE * 3;
                            drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                            dstx += TILE_SIZE;
                        }else if (map.tile[i][j] == '4'){
                            srcx = TILE_SIZE * 4;
                            drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                            dstx += TILE_SIZE;
                        }else{
                            dstx += TILE_SIZE;
                        }
                    }
                    dsty += TILE_SIZE;
                }
            }



void changeLevel(void){

    //char file[200];

    /* Charge la map depuis le fichier */
    //sprintf(file, "map/map%d.txt", getLevel());
    loadMap("map/map1.txt");

    //Charge le tileset
    if (map.tileSet != NULL){
        SDL_DestroyTexture(map.tileSet);
    }
    /*if (map.tileSetB != NULL){
        SDL_DestroyTexture(map.tileSetB);
    }*/

    //sprintf(file, "graphics/tileset%d.png", map.tilesetAffiche);
    map.tileSet = loadImage("sprites/tileset.png");

    //sprintf(file, "graphics/tileset%dB.png", map.tilesetAffiche);
    //map.tileSetB = loadImage(file);
}


void cleanMaps(void){
    // Libère la texture du background
    if (map.background != NULL){
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }

    // Libère les textures des tilesets
    if (map.tileSet != NULL){
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }

    /*if (map.tileSetB != NULL){
        SDL_DestroyTexture(map.tileSetB);
        map.tileSetB = NULL;
    }*/
}

int getStartX(void)
{
return map.startX;
}

void setStartX(int valeur)
{
map.startX = valeur;
}

int getStartY(void)
{
return map.startY;
}

void setStartY(int valeur)
{
map.startY = valeur;
}

int getMaxX(void)
{
return map.maxX;
}

int getMaxY(void)
{
return map.maxY;
}

int getBeginX(void)
{
return map.beginx;
}

int getBeginY(void)
{
return map.beginy;
}

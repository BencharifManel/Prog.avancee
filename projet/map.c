#include "prototypes.h"


void initMaps(Map *map){
    // Charge le background
    map->background = loadImage("sprites/background.png");
}

SDL_Texture *getBackground(Map *map){
    return map->background;
}

void loadMap(char *name, Map *map){
    //On ouvre le fichier et v�rifie qu'il est non NULL
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
            }else{
                map->tile[i][j] = c;
                j ++;
            }
        } while (c != EOF);
                    fclose (pFile);
    }
}

void drawMap(Map *map){
    int dstx = 0;
    int dsty = 0;
    int srcx = 0;
    int srcy = 0;
    for(int i = 0; i < 9; i++) {
        dstx = 0;
        for(int j = 0; j < 13 ; j++) {
            if (map->tile[i][j] == '0') {
                srcx = TILE_SIZE * 0;
                drawTile(map->tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map->tile[i][j] == '1'){
                srcx = TILE_SIZE * 1;
                drawTile(map->tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map->tile[i][j] == '2'){
                srcx = TILE_SIZE * 2;
                drawTile(map->tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map->tile[i][j] == '3'){
                srcx = TILE_SIZE * 3;
                drawTile(map->tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map->tile[i][j] == '4'){
                srcx = TILE_SIZE * 4;
                drawTile(map->tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else{
                dstx += TILE_SIZE;
            }
        }
        dsty += TILE_SIZE;
    }
}

void changeLevel(Map *map){

    //Chargement de la map depuis le fichier
    loadMap("map/map1.txt", map);

    //Chargement du tileset
    if (map->tileSet != NULL){
        SDL_DestroyTexture(map->tileSet);
    }
    map->tileSet = loadImage("sprites/tileset.png");
}

void cleanMaps(Map *map){
    // Lib�re la texture du background
    if (map->background != NULL){
        SDL_DestroyTexture(map->background);
        map->background = NULL;
    }

    // Lib�re les textures des tilesets
    if (map->tileSet != NULL){
        SDL_DestroyTexture(map->tileSet);
        map->tileSet = NULL;
    }
}

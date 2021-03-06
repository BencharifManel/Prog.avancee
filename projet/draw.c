#include "prototypes.h"


void drawGame(Map *map, GameObject *player){
    // Affiche le background � 0,0
    drawImage(getBackground(map), 0, 0);

    // Affiche la map de tiles
    drawMap(map);

    // Affiche le joueur
    drawPlayer(player);

    // Affiche l'�cran
    SDL_RenderPresent(getrenderer());

    SDL_Delay(1);
}



SDL_Texture *loadImage(char *name){
    /* Charge les images dans SDL_Surface */
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;
    image = IMG_Load(name);

    if (image != NULL){
        // Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(getrenderer(), image);

        // On se d�barrasse du pointeur vers une surface
        SDL_FreeSurface(image);
        image = NULL;
    }else
        printf("ERROR : chargement de l'image");

    return texture;

}


void drawImage(SDL_Texture *image, int x, int y){

    SDL_Rect dest;

    /* R�gle le rectangle � dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;

    /* Dessine l'image enti�re sur l'�cran aux coordonn�es x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getrenderer(), image, NULL, &dest);

}



void delay(unsigned int frameLimit){
    //60 images/seconde
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks){
        return;
    }

    if (frameLimit > ticks + 16){
        SDL_Delay(16);
    }else{
        SDL_Delay(frameLimit - ticks);
    }
}


void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy){
    //Rectangle de destination � dessiner
    SDL_Rect dest;

    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;

    /* Rectangle source */
    SDL_Rect src;

    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    /* Dessine la tile choisie sur l'�cran aux coordonn�es x et y */
    SDL_RenderCopy(getrenderer(), image, &src, &dest);
}

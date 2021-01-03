#include "../headers/prototypes.h"




void drawGame(void)
{
// Affiche le fond (background) aux coordonn�es (0,0)
drawImage(getBackground(), 0, 0);

/* Affiche la map de tiles : layer 2 (couche du fond) */
drawMap();

/* Affiche le joueur */
drawPlayer();

// Affiche l'�cran
SDL_RenderPresent(getrenderer());

// D�lai pour laisser respirer le proc
SDL_Delay(1);
}



SDL_Texture *loadImage(char *name){
    /* Charge les images avec SDL Image dans une SDL_Surface */
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);

    if (loadedImage != NULL){
        // Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);

        // On se d�barrasse du pointeur vers une surface
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
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
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy){
    /* Rectangle de destination � dessiner */
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

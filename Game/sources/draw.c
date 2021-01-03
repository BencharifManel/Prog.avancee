#include "../headers/prototypes.h"


void drawGame(void){
    // Affiche le background à 0,0
    drawImage(getBackground(), 0, 0);

    // Affiche la map de tiles
    drawMap();

    // Affiche le joueur
    drawPlayer();

    // Affiche l'écran
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

        // On se débarrasse du pointeur vers une surface
        SDL_FreeSurface(image);
        image = NULL;
    }else
        printf("ERROR : chargement de l'image");

    return texture;

}

TTF_Font *loadFont(char *name, int font_size){
    TTF_Font *font = TTF_OpenFont(name, font_size);
    if(font == NULL){
        printf("ERROR : chargement font: \n");
    }
    return font;
}

void drawImage(SDL_Texture *image, int x, int y){

    SDL_Rect dest;

    /* Règle le rectangle à dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;

    /* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getrenderer(), image, NULL, &dest);

}

void drawTexte(TTF_Font *font, int x, int y, char *text){
    SDL_Color noir = { 0, 0, 0 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, noir);
    //printf("FFFFF\n");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(getrenderer(), surface);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_RenderCopy(getrenderer(), texture, NULL, &dst);
}

void drawScore(SDL_Renderer *renderer, GameObject *player,TTF_Font *font){
	char score[20];
   	sprintf(score, "Score : %d", player->score); // Conversion de l'entier
    drawTexte(font,0,0,"SCORE");

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
    //Rectangle de destination à dessiner
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

    /* Dessine la tile choisie sur l'écran aux coordonnées x et y */
    SDL_RenderCopy(getrenderer(), image, &src, &dest);
}


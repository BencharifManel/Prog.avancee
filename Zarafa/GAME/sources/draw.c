#include "../headers/prototypes.h"


void drawGame(void){
    // Affiche le background � 0,0
    drawImage(getBackground(), 0, 0);

    // Affiche la map de tiles
    drawMap();

    // Affiche le joueur
    drawPlayer();

    // Affiche l'�cran
    SDL_RenderPresent(getrenderer());

    SDL_Delay(1);
}

void drawMenu(void){
    //background
    drawImage(getBackground(), 0, 0);

    //tete girafe
    SDL_Texture *tete = loadImage("../sprites/tete.png");
    drawImage(tete, 0, 226);

    //titre
    SDL_Texture *titre = loadImage("../sprites/titre.png");
    drawImage(titre, 266, 75);

    //commande
    SDL_Texture *commande = loadImage("../sprites/commande.png");
    drawImage(commande, 332, 457);

    //bouton quitter
    SDL_Texture *quitter = loadImage("../sprites/quitter.png");
    drawImage(quitter, 480, 240);

    //bouton jouer
    SDL_Texture *jouer = loadImage("../sprites/jouer.png");
    drawImage(jouer, 180, 240);

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

TTF_Font *loadFont(char *name, int font_size){
    TTF_Font *font = TTF_OpenFont(name, font_size);
    if(font == NULL){
        printf("ERROR : chargement font: \n");
    }
    return font;
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

void drawTexte(TTF_Font *font, int x, int y, int w, int h, char *text){
    SDL_Color noir = { 0, 0, 0 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, noir);
    //printf("FFFFF\n");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(getrenderer(), surface);
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(getrenderer(), texture, NULL, &dst);
}

void drawScore(SDL_Renderer *renderer, GameObject *player,TTF_Font *font){
    char score[20];
    //Score
    drawTexte(font,650,50,75, 23,"Score : ");
   	sprintf(score, "%d", player->score); // Conversion de l'entier
    drawTexte(font,725,50,23,23,score);
    //Best score
    drawTexte(font,575,10,150, 23,"Meilleur score : ");
   	sprintf(score, "%d", readScore("../score/score.txt")); // Conversion de l'entier
    drawTexte(font,725,10,23,23,score);
}
void drawTitre(SDL_Renderer *renderer, TTF_Font *font){
    drawTexte(font,100,100,75, 23,"ZARAFA");
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

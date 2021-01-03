#include "prototypes.h"


SDL_Window *screen;
SDL_Renderer *renderer;


SDL_Renderer *getrenderer(void){
    return renderer;
}


void init(char *title){
    //Cr�ation de la fen�tre

    screen = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);

    //Cr�ation du renderer
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

    // Si erreur
    if (screen == NULL || renderer == NULL){
        printf("ERROR : cr�ation de la fen�tre ou du renderer\n");
        exit(1);
    }

    //Initialisation de SDL_image, pour les images .png
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        printf("ERROR : initialisation de SDL_image\n");
        exit(1);
    }

    //Pour faire disparaitre le curseur de l'�cran
    SDL_ShowCursor(SDL_DISABLE);
}



void cleanup(){
    //On lib�re la m�moire

    //Sprites de la map
        cleanMaps();

    //Sprite du h�ros
    cleanPlayer();

    //Fen�tre et renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;

    //SDL
    SDL_Quit();
}


void loadGame(Map map, GameObject player){
    initMaps(map);

    initPlayerSprites(map, player);

    changeLevel();
}

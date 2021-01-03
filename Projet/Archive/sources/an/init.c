#include "../headers/prototypes.h"


SDL_Window *screen;
SDL_Renderer *renderer;


SDL_Renderer *getrenderer(void){
    return renderer;
}


void init(char *title)
{
    //Cr�ation de la fen�tre

    screen = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);

    //Cr�ation du renderer (SDL_RENDERER_PRESENTVSYNC permet une meilleur qualit� d'image)
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

    // Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
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

    //Initialisation de SDL_ttf, pour les textes
    if (TTF_Init() < 0){
        printf("ERROR : initialisation de SDL_ttf\n");
        exit(1);
    }

/*
    //Initialisation de SDL_mixer, pour la musique
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags){
        printf("ERROR : initialisation de SDL_mixer\n");
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }

    //D�finition du nombre de pistes audios
    Mix_AllocateChannels(32);
*/
}



void cleanup(){
    //On lib�re la m�moire

    //Sprites de la map
        cleanMaps();

    //NOUVEAU : Lib�re le sprite du h�ros
    cleanPlayer();

  /*  //SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();*/

    //Fen�tre et renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;

    //SDL_ttf
    TTF_Quit();

    //SDL
    SDL_Quit();
}


void loadGame(void)
{

//On charge les donn�es pour la map
initMaps();


//NOUVEAU : On charge la feuille de sprites (spritesheet) de notre h�ros

initPlayerSprites();

//On commence au premier niveau
SetValeurDuNiveau(1);
changeLevel();

}

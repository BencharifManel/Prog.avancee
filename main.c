/**
 * \file main.c
 * \author Bencharif Manel
 */
#include "fonctions_fichiers.h"
int main(int argc, char** argv){


  /*int nbLig;
  int nbCol;
  char** tab = allouer_tab_2D(5,7);
  afficher_tab_2D(tab,5,7);
  //desallouer_tab_2D(tab , 5);
  taille_fichier("tab.txt" ,&nbLig,&nbCol);
  printf("%d\n",nbLig );
  printf("%d",nbCol );
  //lire_fichier("tabCaracteres.txt");
  tab[2][3] = '3';
  modifier_caractere(tab, 5, 7, '1', '2');
  afficher_tab_2D(tab,5,7);
  ecrire_fichier("new.txt", tab, 5, 7);
  desallouer_tab_2D(tab , 5);*/


//////////////////////////////////////////////////////////////// SDL2

  // Déclaration de la fenêtre
  SDL_Window* window;
  // Événements liés à la fenêtre
  SDL_Event evenements;
  // Le renderer
  SDL_Renderer* renderer;
  //SDL_Surface* surface;
  //SDL_Rect des_rect ={0,0,640,480};
  bool terminer = false;

  // Initialisation de la SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    window = SDL_CreateWindow("Projet",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                600, 600, SDL_WINDOW_RESIZABLE );

    // En cas d’erreur
    if(window == NULL){
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /*****************************************************************/
    // Mettre en place un contexte de rendu de l’écran
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // En cas d’erreur
    if(renderer == NULL){
        printf("Erreur de la creation du rendu: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    SDL_RenderPresent(renderer);
    SDL_Delay(3000);


    /*****************************************************************/




    // Charger l’image
    SDL_Texture* texture = charger_image("pavage.bmp", renderer );
    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;

    SDL_Texture* obj = charger_image_transparente("obj.bmp", renderer,r,g,b);
    SDL_Texture* sprite = charger_image_transparente("sprites.bmp" ,renderer,0 ,g,b);
    int objetW ;
    int objetH;

    SDL_QueryTexture(obj, NULL ,NULL ,&objetW , &objetH);  //charger_image(picture, renderer );

    int sprtW ;
        int sprtH;

        SDL_QueryTexture(sprite, NULL ,NULL ,&sprtW , &sprtH);

SDL_RenderCopy(renderer, texture, NULL, NULL);
    // Libération de l’écran (renderer)
    SDL_DestroyRenderer(renderer);
    //SDL_DestroyTexture(sprite);
    //SDL_DestroyTexture(obj);
    //SDL_DestroyTexture(fond);
    //SDL_DestroyTexture(texte);
    // Fermer la police et quitter SDL_ttf
    TTF_Quit();
    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0;
}

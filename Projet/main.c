/**
 * \file main.c
 * \author Bencharif Manel
 */
#include "fonctions_fichiers.h"
int main(int argc, char** argv){

  //Test allouer_tab_2D, desallouer_tab_2D, afficher_tab_2D et modifier_caractere

  char** tab = allouer_tab_2D(5,7);
  printf("\nAffichage du tableau vide :\n");
  afficher_tab_2D(tab,5,7);
  tab[2][3] = '3';
  modifier_caractere(tab, 5, 7, ' ', '0');
  printf("\nAffichage du tableau rempli de 0 avec tab[2][3] ='3':\n");
  afficher_tab_2D(tab,5,7);
  desallouer_tab_2D(tab , 5);


  //Test taille_fichier, lire_fichier, ecrire_fichier
  int line;
  int colon;
  taille_fichier("terrain.txt" ,&line,&colon);
  printf("\nNombre de lignes de tab.txt : %d\n", line );
  printf("Nombre de colonnes de tab.txt : %d\n", colon );
  //taille_fichier("terrain.txt", &line, &colon);
  //char** tab1 = lire_fichier("tab.txt");
  //afficher_tab_2D(tab1, line, colon);
  //ecrire_fichier("tab.txt", tab1, line, colon);

  //////////////////////////////////////////////////////////////// SDL2

    // Déclaration de la fenêtre
    SDL_Window* window = NULL;
    // Événements liés à la fenêtre
    SDL_Event evenements ;
    // Le renderer
    SDL_Renderer* renderer = NULL ;
    SDL_Surface* picture;
    SDL_Rect des_rect ={0,0,640,480};
    bool terminer = false;
    SDL_Texture *texture =NULL;

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


    // Charger l’image
      picture = SDL_LoadBMP("pavage.bmp");
      if(picture == NULL){
        printf("Erreur au niveau de l'image: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
      }

      texture = SDL_CreateTextureFromSurface(renderer ,picture);
      SDL_FreeSurface(picture);

      // En cas d’erreur
      if(texture == NULL){
          printf("Erreur pour texture: %s",SDL_GetError());
          SDL_Quit();
          return EXIT_FAILURE;
      }

      if(SDL_QueryTexture(texture, NULL, NULL, &des_rect.w, &des_rect.h) != 0){
        printf("Erreur pour SDL_QueryTexture: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
      }

      if(SDL_RenderCopy(renderer, texture, NULL, &des_rect) != 0){
        printf("Erreur pour SDL_RenderCopy: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
      }





    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    //clean_ressources(window, renderer, texture);


    return EXIT_SUCCESS;
}
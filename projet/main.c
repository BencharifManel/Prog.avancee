#include "prototypes.h"

/* D�claration des variables / structures utilis�es par le jeu */
Input input;
GameObject player;
Map map;

int main(int argc, char *argv[])
{
  unsigned int frameLimit = SDL_GetTicks() + 16;
  int go;

  // Initialisation de la SDL
  init("Jeu");

  // Chargement des ressources (graphismes, sons)
  loadGame(&map);

  /* On initialise le joueur */
  initializePlayer(&player);

  // Appelle la fonction cleanup � la fin du programme
  //atexit(cleanup);
  atexit(cleanup(&map));

  go = 1;

  // Boucle infinie, principale, du jeu
  while (go == 1)
  {
    //Gestion des inputs clavier
    getInput(&input);

    // On met � jour le jeu, en commen�ant par le joueur
    updatePlayer(&input, &player, &map);

    //On dessine tout
    drawGame(&map, &player);

    // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
    delay(frameLimit);
    frameLimit = SDL_GetTicks() + 16;
  }

  // On quitte
  exit(0);

}

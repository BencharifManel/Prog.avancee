
/**
 * \file fonctions_SDL.h
 * \author Bencharif Manel
 * \brief fichier d'en tête
 */
 #include <SDL2/SDL.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include <SDL2/SDL_ttf.h>
 #include "fonctions_SDL.h"


#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H
 char** allouer_tab_2D(int n, int m);
 //allouer un tableau de caractères detaillen◊m, où n et m sont les nombres de lignes et de colonnes,
 //et initialiserce tableau avec le caractère espace (’ ’)

 void desallouer_tab_2D(char** tab, int n);
 //libérer un tableau à deuxdimensions, denlignes.

 void afficher_tab_2D(char** tab, int n, int m);
  //afficher le contenu d’untableau de caractères de taille m

 void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
 //compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichierdont le nom estnomFichier.

 char** lire_fichier(const char* nomFichier);
 /*lire un fichier dont le nomestnomFichier,
  et retourner le tableau qui contient les caractères du fichier
  tel qu’une ligne du tableau correspond à une ligne du fichier */

  char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);
  /* Retourner un nouveau tableau, dans lequel toutes les occurrences du caractère ancien sont remplacées par le caractère nouveau. */

  void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);
  /* Écrire le tableautabde taille n x m dans un fichier dont le nom estnomFichier. */
  #endif

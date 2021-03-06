#ifndef STRUCTURES
#define STRUCTURES

#include "param.h"

//*** Les structures seront regroup�es ici ***

//Input : g�rer le clavier
typedef struct Input{

    int left, right, up, down, jump, attack, enter, erase, pause;

} Input;

//Map : g�rer la map
typedef struct Map{

    SDL_Texture *background;
    SDL_Texture *tileSet;

    // Coordonn�es de d�part du h�ros
    int beginx, beginy;


    // Tableau contenant les infos du fichier
    char tile[MAP_Y][MAP_X];

} Map;

// Structure pour g�rer nos sprites
typedef struct GameObject{
    // Coordonn�es du sprite
    int x, y;

    // Largeur, hauteur du sprite
    int h, w;

    // Pour l'animation
    int frameNumber, frameTimer, frameMax;
    // etat : IDLE, WALK etc...
    int etat, direction;


    //s'il est sur le sol/mort
    int onGround, timerMort;
    //Vecteurs de d�placement temporaires (pour collision)
    float dirX, dirY;

} GameObject;

#endif

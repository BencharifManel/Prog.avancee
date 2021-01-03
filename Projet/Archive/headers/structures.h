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
    SDL_Texture *tileSet;/*, *tileSetB;*/

    /* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
    int beginx, beginy;

    /* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonn�es max de fin de la map */
    int maxX, maxY;

    /* Tableau � double dimension repr�sentant la map de tiles */
    char tile[MAX_MAP_Y][MAX_MAP_X];

    //Deuxi�me couche de tiles
    //int tile2[MAX_MAP_Y][MAX_MAP_X];

    //Troisi�me couche de tiles
    //int tile3[MAX_MAP_Y][MAX_MAP_X];

    /* Timer et num�ro du tileset � afficher pour animer la map */
    int mapTimer, tileSetNumber;

} Map;

// Structure pour g�rer nos sprites
typedef struct GameObject
{

// Points de vie/sant� + chrono d'invicibilit�
int life, invincibleTimer;

// Coordonn�es du sprite
int x, y;

// Largeur, hauteur du sprite
int h, w;

// Checkpoint pour le h�ros (actif ou non)
int checkpointActif;
// + coordonn�es de respawn (r�apparition)
int respawnX, respawnY;


// Variables utiles pour l'animation :
// Num�ro de la frame (= image) en cours + timer
int frameNumber, frameTimer, frameMax;
// Nombre max de frames, �tat du sprite et direction
// dans laquelle il se d�place (gauche / droite)
int etat, direction;


// Variables utiles pour la gestion des collisions :
//Est-il sur le sol, chrono une fois mort
int onGround, timerMort;
//Vecteurs de d�placement temporaires avant d�tection
//des collisions avec la map
float dirX, dirY;
//Sauvegarde des coordonn�es de d�part
int saveX, saveY;

//Variable pour le double saut
int jump;


} GameObject;

#endif

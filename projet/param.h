#ifndef PARAM
#define PARAM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

//Pour les images non .bmp
#include <SDL2/SDL_image.h>
//Pour les textes
#include <SDL2/SDL_ttf.h>
//Pour les musiques
//#include <SDL2/SDL_mixer.h>

//Param�tres fen�tre
#define SCREEN_WIDTH 832
#define SCREEN_HEIGHT 576

/* Taille maxi de la map : 20 x 15 tiles */
#define MAX_MAP_X 13
#define MAX_MAP_Y 9

/* Taille d'une tile (64 x 64 pixels) */
#define TILE_SIZE 64

/* Constantes pour l'animation */

#define TIME_BETWEEN_2_FRAMES_PLAYER 4

/* Taille du sprite de notre h�ros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 64
#define PLAYER_HEIGTH 64

//Vitesse de d�placement en pixels du sprite
#define PLAYER_SPEED 4

//Valeurs attribu�es aux �tats/directions
#define IDLE 0
#define WALK 1
#define JUMP1 2
#define DEAD 3

#define RIGHT 1
#define LEFT 2

//Constantes d�finissant la gravit� et la vitesse max de chute
#define GRAVITY_SPEED 0.4
#define MAX_FALL_SPEED 10
#define JUMP_HEIGHT 10

#endif

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

//Paramètres fenêtre
#define SCREEN_WIDTH 832
#define SCREEN_HEIGHT 576

/* Taille maxi de la map : 20 x 15 tiles */
#define MAP_X 13
#define MAP_Y 9

/* Taille d'une tile (64 x 64 pixels) */
#define TILE_SIZE 64

/* Constantes pour l'animation */

#define TIME_BETWEEN_2_FRAMES_PLAYER 4

/* Taille du sprite de notre héros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 64
#define PLAYER_HEIGTH 64

//Vitesse de déplacement en pixels du sprite
#define PLAYER_SPEED 2

//Valeurs attribuées aux états/directions
#define IDLE 0
#define WALK 1
#define JUMP1 2
#define DEAD 3

#define RIGHT 1
#define LEFT 2

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 0.4
#define MAX_FALL_SPEED 10
#define JUMP_HEIGHT 40
#define JUMP_TIMER 7

#endif

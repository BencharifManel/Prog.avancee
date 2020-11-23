/**
 * \file fonctions_SDL.c
 * \author Bencharif Manel
 * \brief fichier source contenant le corps des fonctions
 */

#include "fonctions_SDL.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer){
    SDL_Surface*surface = SDL_LoadBMP(nomfichier);
    SDL_Texture*texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}
SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface*surface = SDL_LoadBMP(nomfichier);
    SDL_SetColorKey(surface ,SDL_TRUE , SDL_MapRGB(surface->format, r,g,b));
    SDL_Texture*texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}

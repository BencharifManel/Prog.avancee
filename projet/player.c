#include "prototypes.h"



int level;
GameObject player;
SDL_Texture *playerSpriteSheet;


GameObject *getPlayer(void){
    return &player;
}


int getPlayerx(void){
    return player.x;
}


int getPlayery(void){
    return player.y;
}


void setPlayerx(int valeur){
    player.x = valeur;
}


void setPlayery(int valeur){
    player.y = valeur;
}


int getLevel(void){
    return level;
}

//Charge la feuille de sprites du pers
//au début du jeu
void initPlayerSprites(void){
    playerSpriteSheet = loadImage("sprites/player.png");
}


//Libère le sprite du héros à la fin du jeu
void cleanPlayer(void){
    if (playerSpriteSheet != NULL){
        SDL_DestroyTexture(playerSpriteSheet);
        playerSpriteSheet = NULL;
    }
}

void initializePlayer(void){
    //Etat et direction au debut du jeu
    player.direction = RIGHT;
    player.etat = IDLE;

    //Numéro de la frame où commencer (0 = IDLE)
    player.frameNumber = 0;

    //Valeur de timer (animation)
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    //1 frame pour l'animation IDLE
    player.frameMax = 1;

    //Coordonnées de départ
    player.x = 64;
    player.y = 64;

    // Hauteur et largeur de notre héros
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;

    //On consider le joueur vivant et pas sur le sol
    player.timerMort = 0;
    player.onGround = 0;
}

void drawPlayer(void){
    // Si compte à rebours arrive à zéro
    if (player.frameTimer <= 0){
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        player.frameNumber++;

        //Pour revenir a la frame de départ
        if (player.frameNumber >= player.frameMax)
            player.frameNumber = 0;
    }
    //Sinon, on décrémente le compte à rebours
    else
        player.frameTimer--;



    //Rectangle de destination à dessiner
    SDL_Rect dest;

    dest.x = player.x;
    dest.y = player.y;
    dest.w = player.w;
    dest.h = player.h;

    //Rectangle source
    SDL_Rect src;

    src.x = player.frameNumber * player.w;
    src.w = player.w;
    src.h = player.h;

    src.y = player.etat * player.h;

    //Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche
    if (player.direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
}




void updatePlayer(Input *input){
    player.onGround = 1;
    player.y = 64;


    //Si on détecte un appui sur la touche fléchée gauche
    if (input->left == 1){
        player.x -= PLAYER_SPEED;
        player.direction = LEFT;

        if (player.etat != WALK && player.onGround == 1){
            player.etat = WALK;
            player.frameNumber = 1;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 2;
        }
    }


    //Si on détecte un appui sur la touche fléchée droite
    else if (input->right == 1){
        player.x += PLAYER_SPEED;
        player.direction = RIGHT;

        if (player.etat != WALK && player.onGround == 1){
            player.etat = WALK;
            player.frameNumber = 1;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 2;
        }
    }


    //Si on n'appuie sur rien et qu'on est sur le sol
    else if (input->right == 0 && input->left == 0 && input->jump == 0 && player.onGround == 1){
        if (player.etat != IDLE){
            player.etat = IDLE;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }
    }

    else if (input->jump == 1){
        player.y -= JUMP_HEIGHT;
        player.direction = RIGHT;

        if (player.etat != JUMP1 && player.onGround == 1){
            player.etat = JUMP1;
            player.frameNumber = 2;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }
    }
}

#include "prototypes.h"


int level;
GameObject player;
Map map;
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

void gravity(Map map2, GameObject player2){
  map2 = map;
  player2 = player;
  // si la position du joueur est sur un truc vide
  if (map.tile[player2.x/64][player2.y/64] == 0) {
    //le joueur tombe sur la case en dessous
    for (int i = 0; i > 63; i++)
      player2.y + i;
  }
}

//Charge la feuille de sprites du pers
//au d�but du jeu
void initPlayerSprites(Map map2, GameObject player2){
    playerSpriteSheet = loadImage("sprites/player.png");
    player2 = player;
    map2 = map;
}

//Lib�re le sprite du h�ros � la fin du jeu
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

    //Num�ro de la frame o� commencer (0 = IDLE)
    player.frameNumber = 0;

    //Valeur de timer (animation)
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    //1 frame pour l'animation IDLE
    player.frameMax = 1;

    //Coordonn�es de d�part
    player.x = 64;
    player.y = 64;

    // Hauteur et largeur de notre h�ros
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;

    //On consider le joueur vivant et pas sur le sol
    player.timerMort = 0;
    player.onGround = 0;
}

void drawPlayer(void){
    // Si compte � rebours arrive � z�ro
    if (player.frameTimer <= 0){
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        player.frameNumber++;

        //Pour revenir a la frame de d�part
        if (player.frameNumber >= player.frameMax)
            player.frameNumber = 0;
    }
    //Sinon, on d�cr�mente le compte � rebours
    else
        player.frameTimer--;

    //Rectangle de destination � dessiner
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

    //Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche
    if (player.direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
}

void updatePlayer(Input *input, Map map2){
    //Debut TEST de l'entourage
      //a gauche
      switch (map2.tile[player.x/64 - 1][player.y/64]){
        case '0':
            printf("il y a terre a gauche\n");
        break;

        case '1':
            printf("il y a 7chich a gauche\n");
        break;

        case '2':
            printf("il y a eau a gauche\n");
        break;

        case '3':
            printf("il y a nuage a gauche\n");
        break;

        case '4':
            printf("il y a plante a gauche\n");
        break;

        default:
            printf("LEFT : map[%d][%d] = %c\n",player.x/64 - 1, player.y/64, map2.tile[player.x/64 - 1][player.y/64]);
            //printf("il y a ni 0 ni 1 ni 2 ni 3 ni 4 a gauche\n");

        break;
      }

      //a droite
      switch (map2.tile[player.x/64 + 1][player.y/64]){
        case '0':
            printf("il y a terre a droite\n");
        break;

        case '1':
            printf("il y a 7chich a droite\n");
        break;

        case '2':
            printf("il y a eau a droite\n");
        break;

        case '3':
            printf("il y a nuage a droite\n");
        break;

        case '4':
            printf("il y a plante a droite\n");
        break;

        default:
          printf("RIGHT : map[%d][%d] = %c\n",player.x/64 + 1, player.y/64, map2.tile[player.x/64 + 1][player.y/64]);
          //printf("il y a ni 0 ni 1 ni 2 ni 3 ni 4 a droite\n");
        break;

      }

      //en haut
      switch (map2.tile[player.x/64][player.y/64 - 1]){
        case '0':
            printf("il y a terre a haut\n");
        break;

        case '1':
            printf("il y a 7chich a haut\n");
        break;

        case '2':
            printf("il y a eau a haut\n");
        break;

        case '3':
            printf("il y a nuage a haut\n");
        break;

        case '4':
            printf("il y a plante a haut\n");
        break;

        default:
            printf("UP : map[%d][%d] = %c\n",player.x/64, player.y/64 - 1, map2.tile[player.x/64][player.y/64 - 1]);
            printf("il y a ni 0 ni 1 ni 2 ni 3 ni 4 a haut\n");
        break;

      }

      // en bas
      switch (map2.tile[player.x/64][player.y/64 + 1]){
        case '0':
            //printf("DOWN : i : %d, j : %d\n",player.x/64, player.y/64 + 1);
            printf("il y a terre a bas\n");
        break;

        case '1':
            printf("il y a 7chich a bas\n");
        break;

        case '2':
            printf("il y a eau a bas\n");
        break;

        case '3':
            printf("il y a nuage a bas\n");
        break;

        case '4':
            printf("il y a plante a bas\n");
        break;

        default:
            printf("DOWN : map[%d][%d] = %c\n",player.x/64, player.y/64 + 1, map2.tile[player.x/64][player.y/64 + 1]);
            //printf("il y a ni 0 ni 1 ni 2 ni 3 ni 4 a bas\n");
        break;

      }
    //Fin TEST de l'entourage

    player.onGround = 1;
    //player.y = 64;

    gravity(map2, player);

    //Si on d�tecte un appui sur la touche fl�ch�e gauche
    if (input->left == 1) {
        player.x -= PLAYER_SPEED;
        player.direction = LEFT;

        if (player.etat != WALK && player.onGround == 1){
            player.etat = WALK;
            player.frameNumber = 1;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 2;
        }
    }

    //Si on d�tecte un appui sur la touche fl�ch�e droite
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

    else if (input->jump == 1) {

        //player.y -= JUMP_HEIGHT;
        player.direction = RIGHT;

        int temp = player.y;

        if (player.etat != JUMP1 && player.onGround == 1) {
            player.etat = JUMP1;
            player.frameNumber = 2;

            int temp = player.y;

            player.y -= JUMP_HEIGHT;

            drawPlayer();
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }

        if (temp == player.y + JUMP_HEIGHT){
          player.y += JUMP_HEIGHT;
          drawPlayer();
        }
    }
}

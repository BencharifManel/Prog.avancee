#include "../headers/prototypes.h"


Map map;
int level;
GameObject player;
SDL_Texture *playerSpriteSheet;

void initMaps(void){
    // Charge le background
    map.background = loadImage("../sprites/background.png");
}

SDL_Texture *getBackground(void){
    return map.background;
}

void loadMap(char *name){
    //On ouvre le fichier et v�rifie qu'il est non NULL
    FILE * pFile;
    int c;
    pFile=fopen (name,"r");
    if (pFile==NULL){
        perror ("Error opening file");
    }
    //Si le fichier est non NULL
    else {
        int i = 0; int j = 0;
        do {
            //On ouvre et parcourt le fichier
            c = fgetc (pFile);
            if ((c == '\n') || (c == '\r')){
                if (c == '\n'){
                i ++;
                j = 0;
                }
            }else{
                map.tile[i][j] = c;
                j ++;
            }
        } while (c != EOF);
                    fclose (pFile);
    }
}

void drawMap(){
    int dstx = 0;
    int dsty = 0;
    int srcx = 0;
    int srcy = 0;
    for(int i = 0; i < 9; i++){
        dstx = 0;
        for(int j = 0; j < 13 ; j++){
            if (map.tile[i][j] == '0'){
                srcx = TILE_SIZE * 0;
                drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map.tile[i][j] == '1'){
                srcx = TILE_SIZE * 1;
                drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map.tile[i][j] == '2'){
                srcx = TILE_SIZE * 2;
                drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map.tile[i][j] == '3'){
                srcx = TILE_SIZE * 3;
                drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else if (map.tile[i][j] == '4'){
                srcx = TILE_SIZE * 4;
                drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                dstx += TILE_SIZE;
            }else{
                dstx += TILE_SIZE;
            }
        }
        dsty += TILE_SIZE;
    }
}



void changeLevel(void){

    //Chargement de la map depuis le fichier
    loadMap("../map/map1.txt");

    //Chargement du tileset
    if (map.tileSet != NULL){
        SDL_DestroyTexture(map.tileSet);
    }
    map.tileSet = loadImage("../sprites/tileset.png");
}

void cleanMaps(void){
    // Lib�re la texture du background
    if (map.background != NULL){
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }

    // Lib�re les textures des tilesets
    if (map.tileSet != NULL){
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }
}

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
//au d�but du jeu
void initPlayerSprites(void){
    playerSpriteSheet = loadImage("../sprites/player.png");
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

void updatePlayer(Input *input){
    player.onGround = 1;
    //player.y = 64;
    if ((player.y != 450) && !(player.x < 560 && player.y == 64) && !(player.x > 208 && player.y == 256)){
        player.y += 1;
    }

    //Si on d�tecte un appui sur la touche fl�ch�e gauche
    if (input->left == 1){
      if (player.x >= 52){

        player.x -= PLAYER_SPEED;
        player.direction = LEFT;

        if (player.etat != WALK && player.onGround == 1){
            player.etat = WALK;
            player.frameNumber = 1;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 2;
        }
        if (player.x >= 560 && player.y == 64){
          do {
            player.y += JUMP_HEIGHT/2;
          } while(player.y <= 256);
          player.y = 256;
        }

        if(player.x <= 208 && player.y == 256){
          do {
            player.y += JUMP_HEIGHT/2;
          } while(player.y <= 450);
          player.y = 450;
        }
      }
    }

    //Si on d�tecte un appui sur la touche fl�ch�e droite
    if (input->right == 1){
        if (player.x <= 716){
          player.x += PLAYER_SPEED;
          player.direction = RIGHT;

          if (player.etat != WALK && player.onGround == 1){
              player.etat = WALK;
              player.frameNumber = 1;
              player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
              player.frameMax = 2;
          }
          if (player.x >= 560 && player.y == 64){
            do {
              player.y += JUMP_HEIGHT/2;
            } while(player.y <= 256);
            player.y = 256;
          }

          if(player.x <= 208 && player.y == 256){
            do {
              player.y += JUMP_HEIGHT/2;
            } while(player.y <= 450);
            player.y = 450;
          }
        }
    }

    if (input->down == 1){
      if ((player.y != 450) && !(player.x < 560 && player.y == 64) && !(player.x > 208 && player.y == 256)){
        player.y += 1;
        player.direction = LEFT;

        if (player.etat != WALK && player.onGround == 1){
            player.etat = WALK;
            player.frameNumber = 1;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 2;
        }
      }
    }

    //Si on n'appuie sur rien et qu'on est sur le sol
    if (input->right == 0 && input->left == 0 && input->jump == 0 && player.onGround == 1){
        if (player.etat != IDLE){
            player.etat = IDLE;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }
    }

    if (input->right == 1 && input->left == 0 && input->jump == 1 && player.onGround == 1){
        if (player.etat != JUMP1){
            player.etat = JUMP1;
            player.direction = RIGHT;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }
    }

    if (input->right == 0 && input->left == 1 && input->jump == 1 && player.onGround == 1){
      if (player.etat != JUMP1 || player.direction != LEFT){
          player.etat = JUMP1;
          player.direction = LEFT;
          player.frameNumber = 0;
          player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
          player.frameMax = 1;
      }
    }

    if (input->jump == 1){
        //player.y -= JUMP_HEIGHT;
        player.direction = RIGHT;
        if (player.etat != JUMP1 && player.onGround == 1) {
            player.etat = JUMP1;
            player.frameNumber = 2;

            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }
    }
}

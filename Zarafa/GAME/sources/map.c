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
    //On ouvre le fichier et verifie qu'il est non NULL
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

int readScore(char *name){
    //On ouvre le fichier et verifie qu'il est non NULL
    FILE * pFile;
    int c;
    pFile=fopen (name,"r");
    if (pFile==NULL){
        return 0;
    }
    //Si le fichier est non NULL
    else {
        fscanf(pFile, "%i", &c);
        fclose (pFile);
    }
    return c;
}

void saveScore(char *name){
    //On ouvre le fichier et verifie qu'il est non NULL
    FILE * pFile;
    pFile=fopen (name,"w+");
    if (pFile==NULL){
        perror ("Error opening file");
    }
    //Si le fichier est non NULL
    else {
        fprintf(pFile, "%i", player.score);
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
            switch (map.tile[i][j]) {
                case'0':
                    srcx = TILE_SIZE * 0;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                case '1':
                    srcx = TILE_SIZE * 1;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                case '2':
                    srcx = TILE_SIZE * 2;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                case'3':
                    srcx = TILE_SIZE * 3;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                case '4':
                    srcx = TILE_SIZE * 4;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                case '5':
                    srcx = TILE_SIZE * 5;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                case '6':
                    srcx = TILE_SIZE * 6;
                    drawTile(map.tileSet, dstx, dsty, srcx, srcy);
                    dstx += TILE_SIZE;
                    break;
                default:
                    dstx += TILE_SIZE;
            }
        }
        dsty += TILE_SIZE;
    }
    TTF_Font *font = loadFont("../polices/score.ttf", 40);
    drawScore(getrenderer(), &player,font);
    TTF_CloseFont(font);
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
    // Libere la texture du background
    if (map.background != NULL){
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }

    // Libere les textures des tilesets
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
//au debut du jeu
void initPlayerSprites(void){
    playerSpriteSheet = loadImage("../sprites/player.png");
}


//Libere le sprite du heros a la fin du jeu
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

    //Numero de la frame ou commencer (0 = IDLE)
    player.frameNumber = 0;

    //Valeur de timer (animation)
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    //1 frame pour l'animation IDLE
    player.frameMax = 1;

    //Coordonnees de depart
    player.x = 64;
    player.y = -64;

    // Hauteur et largeur de notre heros
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;

    //On considere le joueur vivant
    player.alive = 1;
    //On consider que le joueur n'est pas sur le sol
    player.timerSaut = 0;
    player.onGround = 0;

    //Le score est � z�ro
    player.score = 0;
}

void drawPlayer(void){
    // Si compte a rebours arrive a zero
    if (player.frameTimer <= 0){
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        player.frameNumber++;

        //Pour revenir a la frame de depart
        if (player.frameNumber >= player.frameMax)
            player.frameNumber = 0;
    }
    //Sinon, on decremente le compte a rebours
    else
        player.frameTimer--;



    //Rectangle de destination a dessiner
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

    //Gestion du flip (retournement de l'image selon que le sprite regarde a droite ou a gauche
    if (player.direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
}

void updatePlayer(Input *input){
    int x1 = (player.x) / TILE_SIZE;
    int x2 = (player.x+ player.w) / TILE_SIZE;
    int y1 = (player.y) / TILE_SIZE;
    int y2 = (player.y + player.h) / TILE_SIZE;
    player.onGround = 0;
    if(player.onGround == 0){
        if ((map.tile[y2][x1] == '1')||(map.tile[y2][x2] == '1')||(map.tile[y2][x1] == '0')||(map.tile[y2][x2] == '0')){
            player.onGround = 1;
        }else
            player.y += 4;
    }

    //Si on detecte un appui sur la touche fleche gauche
    if (input->left == 1){

        if ((map.tile[y2][x1] != '0')&&(map.tile[y2][x1] != '0')) {
            player.direction = LEFT;
            player.x -= PLAYER_SPEED;

            if (player.etat != WALK && player.onGround == 1){
                player.etat = WALK;
                player.frameNumber = 1;
                player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                player.frameMax = 2;
            }
        }
    }

    //Si on detecte un appui sur la touche fleche droite
    if (input->right == 1){
        if ((map.tile[y2][x2] != '0')&&(map.tile[y2][x2] != '0')) {
          player.x += PLAYER_SPEED;
          player.direction = RIGHT;

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
    if (player.timerSaut != 0)
        player.timerSaut -= 1;
    else{
        if (input->jump == 1 && player.onGround == 1){
            if ((map.tile[y1-1][x1] != '0')&&(map.tile[y1-1][x2] != '0')) {
                player.y -= JUMP_HEIGHT;
                player.onGround = 0;
                if (player.etat != JUMP1){
                    player.etat = JUMP1;
                    player.direction = player.direction;
                    player.frameNumber = 0;
                    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                    player.frameMax = 1;
                }
            }
        }
        player.timerSaut = JUMP_TIMER;
    }

    //Pour les rcompenses (cerises)
    if(map.tile[y2][x1] == '5'){
        map.tile[y2][x1] = '-';
        player.score += 10;
    }else if(map.tile[y2][x2] == '5'){
        map.tile[y2][x2] = '-';
        player.score += 10;
    }else if(map.tile[y1][x1] == '5'){
        map.tile[y1][x1] = '-';
        player.score += 10;
    }else if(map.tile[y1][x2] == '5'){
        map.tile[y1][x2] = '-';
        player.score += 10;
    }

    //Pour l'arriv�e
    if(map.tile[y1][x1] == '6'){
        if(player.score > readScore("../score/score.txt"))
            saveScore("../score/score.txt");
        input->jouer = 0;
        initializePlayer();
    }

    //Pour la mort
    if(y2*TILE_SIZE > SCREEN_HEIGHT){
        player.alive = 0;
        input->jouer = 0;
        initializePlayer();
    }

}

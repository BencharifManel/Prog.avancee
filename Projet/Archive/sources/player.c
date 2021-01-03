#include "prototypes.h"



int level;
GameObject player;
SDL_Texture *playerSpriteSheet;


//Renvoie le GameObject player (héros)
GameObject *getPlayer(void)
{
return &player;
}


//Renvoie les coordonnées x du héros
int getPlayerx(void)
{
return player.x;
}


//Renvoie les coordonnées y du héros
int getPlayery(void)
{
return player.y;
}


//Change la valeur des coordonnées x du héros
void setPlayerx(int valeur)
{
player.x = valeur;
}


//Change la valeur des coordonnées y du héros
void setPlayery(int valeur)
{
player.y = valeur;
}


//Renvoie le numéro du niveau en cours
int getLevel(void)
{
return level;
}


//Change la valeur du niveau en cours
void SetValeurDuNiveau(int valeur)
{
level = valeur;
}

//Charge la spritesheet (= feuille de sprites) de notre héros
//au début du jeu
void initPlayerSprites(void)
{
playerSpriteSheet = loadImage("sprites/player.png");
}


//Libère le sprite du héros à la fin du jeu
void cleanPlayer(void)
{
if (playerSpriteSheet != NULL)
{
SDL_DestroyTexture(playerSpriteSheet);
playerSpriteSheet = NULL;
}
}

void initializePlayer(void)
{

//PV à 3
player.life = 3;

//Timer d'invincibilité à 0
player.invincibleTimer = 0;

//Indique l'état et la direction de notre héros
player.direction = RIGHT;
player.etat = IDLE;

//Indique le numéro de la frame où commencer
player.frameNumber = 0;

//...la valeur de son chrono ou timer
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//... et son nombre de frames max (8 pour l'anim' IDLE
// = ne fait rien)
player.frameMax = 1;

player.x = 64;
player.y = 64;

/* Hauteur et largeur de notre héros */
player.w = PLAYER_WIDTH;
player.h = PLAYER_HEIGTH;

//Variables nécessaires au fonctionnement de la gestion des collisions
player.timerMort = 0;
player.onGround = 0;

}

void drawPlayer(void)
{
/* Gestion du timer */
// Si notre timer (un compte à rebours en fait) arrive à zéro
if (player.frameTimer <= 0)
{
//On le réinitialise
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
player.frameNumber++;

//Mais si on dépasse la frame max, il faut revenir à la première :
if (player.frameNumber >= player.frameMax)
player.frameNumber = 0;

}
//Sinon, on décrémente notre timer
else
    player.frameTimer--;


//Ensuite, on peut passer la main à notre fonction

/* Rectangle de destination à dessiner */
SDL_Rect dest;

// On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
//au scrolling :
dest.x = player.x - getStartX();
dest.y = player.y - getStartY();
dest.w = player.w;
dest.h = player.h;

/* Rectangle source */
SDL_Rect src;

//Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
//la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
src.x = player.frameNumber * player.w;
src.w = player.w;
src.h = player.h;

//On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros :
//Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
//Tout cela en accord avec notre spritesheet, of course ;)
src.y = player.etat * player.h;

//Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche
if (player.direction == LEFT)
SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
else
SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);

}




void updatePlayer(Input *input)
{
//Pour l'instant, on place automatiquement le joueur
//sur le sol à 302 pixels du haut de l'écran, car
//on ne gère pas encore les collisions avec le sol.
player.onGround = 64;
player.y = 64;


//Si on détecte un appui sur la touche fléchée gauche
if (input->left == 1)
{
//On diminue les coordonnées en x du joueur
player.x -= PLAYER_SPEED;
//Et on indique qu'il va à gauche (pour le flip
//de l'affichage, rappelez-vous).
player.direction = LEFT;


//Si ce n'était pas son état auparavant et qu'il est bien sur
//le sol (car l'anim' sera différente s'il est en l'air)
if (player.etat != WALK && player.onGround == 1)
{
//On enregistre l'anim' de la marche et on l'initialise à 0
player.etat = WALK;
player.frameNumber = 1;
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
player.frameMax = 2;
}
}


//Si on détecte un appui sur la touche fléchée droite
else if (input->right == 1)
{
//On augmente les coordonnées en x du joueur
player.x += PLAYER_SPEED;
//Et on indique qu'il va à droite (pour le flip
//de l'affichage, rappelez-vous).
player.direction = RIGHT;


//Si ce n'était pas son état auparavant et qu'il est bien sur
//le sol (car l'anim' sera différente s'il est en l'air)
if (player.etat != WALK && player.onGround == 1)
{
//On enregistre l'anim' de la marche et on l'initialise à 0
player.etat = WALK;
player.frameNumber = 1;
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
player.frameMax = 1;
}
}


//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant
//l'inactivité (Idle)
else if (input->right == 0 && input->left == 0 && player.onGround == 1)
{
//On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
//à chaque tour de boucle
if (player.etat != IDLE)
{
//On enregistre l'anim' de l'inactivité et on l'initialise à 0
player.etat = IDLE;
player.frameNumber = 0;
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
player.frameMax = 1;
}

}
}



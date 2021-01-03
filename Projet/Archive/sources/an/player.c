#include "../headers/prototypes.h"



int level;
GameObject player;
SDL_Texture *playerSpriteSheet;


//Renvoie le GameObject player (h�ros)
GameObject *getPlayer(void)
{
return &player;
}


//Renvoie les coordonn�es x du h�ros
int getPlayerx(void)
{
return player.x;
}


//Renvoie les coordonn�es y du h�ros
int getPlayery(void)
{
return player.y;
}


//Change la valeur des coordonn�es x du h�ros
void setPlayerx(int valeur)
{
player.x = valeur;
}


//Change la valeur des coordonn�es y du h�ros
void setPlayery(int valeur)
{
player.y = valeur;
}


//Renvoie le num�ro du niveau en cours
int getLevel(void)
{
return level;
}


//Change la valeur du niveau en cours
void SetValeurDuNiveau(int valeur)
{
level = valeur;
}

//Charge la spritesheet (= feuille de sprites) de notre h�ros
//au d�but du jeu
void initPlayerSprites(void)
{
playerSpriteSheet = loadImage("../sprites/player.png");
}


//Lib�re le sprite du h�ros � la fin du jeu
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

//PV � 3
player.life = 3;

//Timer d'invincibilit� � 0
player.invincibleTimer = 0;

//Indique l'�tat et la direction de notre h�ros
player.direction = RIGHT;
player.etat = IDLE;

//Indique le num�ro de la frame o� commencer
player.frameNumber = 0;

//...la valeur de son chrono ou timer
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//... et son nombre de frames max (8 pour l'anim' IDLE
// = ne fait rien)
player.frameMax = 1;

player.x = 64;
player.y = 64;

/* Hauteur et largeur de notre h�ros */
player.w = PLAYER_WIDTH;
player.h = PLAYER_HEIGTH;

//Variables n�cessaires au fonctionnement de la gestion des collisions
player.timerMort = 0;
player.onGround = 0;

}

void drawPlayer(void)
{
/* Gestion du timer */
// Si notre timer (un compte � rebours en fait) arrive � z�ro
if (player.frameTimer <= 0)
{
//On le r�initialise
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//Et on incr�mente notre variable qui compte les frames de 1 pour passer � la suivante
player.frameNumber++;

//Mais si on d�passe la frame max, il faut revenir � la premi�re :
if (player.frameNumber >= player.frameMax)
player.frameNumber = 0;

}
//Sinon, on d�cr�mente notre timer
else
    player.frameTimer--;


//Ensuite, on peut passer la main � notre fonction

/* Rectangle de destination � dessiner */
SDL_Rect dest;

// On soustrait des coordonn�es de notre h�ros, ceux du d�but de la map, pour qu'il colle
//au scrolling :
dest.x = player.x - getStartX();
dest.y = player.y - getStartY();
dest.w = player.w;
dest.h = player.h;

/* Rectangle source */
SDL_Rect src;

//Pour conna�tre le X de la bonne frame � dessiner, il suffit de multiplier
//la largeur du sprite par le num�ro de la frame � afficher -> 0 = 0; 1 = 40; 2 = 80...
src.x = player.frameNumber * player.w;
src.w = player.w;
src.h = player.h;

//On calcule le Y de la bonne frame � dessiner, selon la valeur de l'�tat du h�ros :
//Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
//Tout cela en accord avec notre spritesheet, of course ;)
src.y = player.etat * player.h;

//Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche
if (player.direction == LEFT)
SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
else
SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);

}




void updatePlayer(Input *input)
{
//Pour l'instant, on place automatiquement le joueur
//sur le sol � 302 pixels du haut de l'�cran, car
//on ne g�re pas encore les collisions avec le sol.
player.onGround = 64;
player.y = 64;


//Si on d�tecte un appui sur la touche fl�ch�e gauche
if (input->left == 1)
{
//On diminue les coordonn�es en x du joueur
player.x -= PLAYER_SPEED;
//Et on indique qu'il va � gauche (pour le flip
//de l'affichage, rappelez-vous).
player.direction = LEFT;


//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
//le sol (car l'anim' sera diff�rente s'il est en l'air)
if (player.etat != WALK && player.onGround == 1)
{
//On enregistre l'anim' de la marche et on l'initialise � 0
player.etat = WALK;
player.frameNumber = 1;
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
player.frameMax = 2;
}
}


//Si on d�tecte un appui sur la touche fl�ch�e droite
else if (input->right == 1)
{
//On augmente les coordonn�es en x du joueur
player.x += PLAYER_SPEED;
//Et on indique qu'il va � droite (pour le flip
//de l'affichage, rappelez-vous).
player.direction = RIGHT;


//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
//le sol (car l'anim' sera diff�rente s'il est en l'air)
if (player.etat != WALK && player.onGround == 1)
{
//On enregistre l'anim' de la marche et on l'initialise � 0
player.etat = WALK;
player.frameNumber = 1;
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
player.frameMax = 1;
}
}


//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant
//l'inactivit� (Idle)
else if (input->right == 0 && input->left == 0 && player.onGround == 1)
{
//On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
//� chaque tour de boucle
if (player.etat != IDLE)
{
//On enregistre l'anim' de l'inactivit� et on l'initialise � 0
player.etat = IDLE;
player.frameNumber = 0;
player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
player.frameMax = 1;
}

}
}

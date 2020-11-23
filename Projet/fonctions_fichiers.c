/**
 * \file fonctions_SDL.c
 * \author Bencharif Manel
 * \brief fichier source contenant le corps des fonctions
 */
 #include "fonctions_fichiers.h"


 char** allouer_tab_2D(int n, int m) {
   char** p;
   p = malloc (sizeof(char*)*n);

   for (int i = 0;i < n; i++)
   p[i] = malloc(sizeof(char)*m);

   for (int i = 0; i < n; i++){
     for (int j = 0; j < m; j++){
        p[i][j] = ' ';
      }
}
if ( *p == NULL){
     fprintf(stderr,"Allocation impossible \n");
     exit(EXIT_FAILURE);
}
return p;
 }
 //allouer un tableau de caractères de taille n m, où n et m sont les nombres de lignes et de colonnes,
 //et initialiserce tableau avec le caractère espace (’ ’)

 void desallouer_tab_2D(char** tab, int n){
   for (int i = 0; i < n; i++){
     free(tab[i]);
   }
   free(tab);
   if ( *tab != NULL){
        fprintf(stderr,"Desallocation impossible \n");
        exit(EXIT_FAILURE);
   }
 }
 //libérer un tableau à deuxdimensions, de n lignes.

 void afficher_tab_2D(char** tab, int n, int m){
   //int tab[n][m];
    int i, j;
    printf(" Le tableau 2D = \n");
    for(i=0; i < n; i++){
      for(j = 0; j < m; j++){
        printf("%c",tab[i][j]);
      }
      printf("\n");
    }
  }
  //afficher le contenu d’untableau de caractères de taille m

 void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
   //On ouvre le fichier et vérifie qu'il est non NULL
   FILE * pFile;
   int c, line = 1 , colon = 0, temp = 0;
   pFile=fopen (nomFichier,"r");
   if (pFile==NULL){
     perror ("Error opening file");
   }
   //Si le fichier est non NULL
   else {
      do {
        //On ouvre et parcourt le fichier
        c = fgetc (pFile);
        //Si c est le caractère retour chariot
        if (c == '\n'){
          //On augmente le nombre de ligne
          line++;
          //On ne garde le maximum du nombre de colonnes
          if (temp >= colon){
            colon = temp;
          }
          temp = 0;
        }
        //Si c n'est pas le caractère retour chariot, on augmente le nombre de colonnes
        else{
          temp++;
        }
      } while (c != EOF);
      if (temp >= colon){
        colon = temp;
      }
      *nbLig = line ;
      *nbCol = colon;
      fclose (pFile);

}

 }
 //compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier dont le nom est nomFichier.

 char** lire_fichier(const char* nomFichier){
   //On ouvre le fichier et vérifie qu'il est non NULL
   FILE * pFile;
   int c;
   pFile=fopen (nomFichier,"r");
   if (pFile==NULL){
     perror ("Error opening file");
   }
   //Si le fichier est non NULL
   else {
      int line; int colon; int i = 0; int j = 0;
      taille_fichier(nomFichier, &line, &colon);
      char** tab = allouer_tab_2D(line,colon);
      do {
        //On ouvre et parcourt le fichier
        c = fgetc (pFile);
        if (c == '\n'){
          i ++;
          j = 0;
        }
        else{
          tab[i][j] = c;
          j ++;
        }
      } while (c != EOF);
        fclose (pFile);
        return tab;
      }
    }
 /*lire un fichier dont le nomestnomFichier,
  et retourner le tableau qui contient les caractères du fichier
  tel qu’une ligne du tableau correspond à une ligne du fichier */

  char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (tab[i][j] == ancien){
                tab[i][j] = nouveau;
            }
        }
    }
    return tab;
  }
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
  FILE * pFile;
  pFile=fopen(nomFichier,"w");
  if (pFile==NULL)
    perror ("Error opening file");
  else {
    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        fputc (tab[i][j],pFile);
      }
      fputc ('\n',pFile);
    }
    if (ferror (pFile))
      perror ("Error Writing to myfile.txt\n");
    fclose (pFile);
  }
}

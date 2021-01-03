# Prog.avancee

Les binômes : BENCHARIF Manel , PLANQUE Manon.

Mise en place, Compilation & Exécution

a / Mise en place :

Télécharger le fichier :  Zarafa.zip

L’extraire, on trouvera :
- Le jeu (qui se trouve dans le dossier jeu final)

- La vidéo démonstrative

- Ce PDF

b / Compilation :

1 – Sur le Terminal se rendre dans l'emplacement du jeu dans le dossier sources car c’est là où se trouve le makefile, par exemple :

                                                          cd '/Bureau/zarafa/sources'
2 – Saisir la commande suivante pour compiler le code :

                                                                  make
2.1 - Optionnellement pour nettoyer les fichiers .o générés :

 c / Exécution :
 
Saisir la commande suivante :

                                                          make mrproper (optionnelle)
                                                                   ./main
Principe & fonctionnement du jeu : 

Pour jouer, on se déplace avec les touches flèche gauche et flèche droite pour se déplacer à gauche et à droite, la touche Espace ou permet de sauter.
Le but est de parcourir la carte en collectant des fruits (cerises) et d’arriver à la porte de destination.

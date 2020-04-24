# Jeu de la Vie (ou Game of Life)

## Description

Projet de Techniques de développement consistant à implémenter et améliorer un automate cellulaire, communément appelé [jeu de la vie](https://fr.wikipedia.org/wiki/Jeu_de_la_vie).
Celui-ci consiste en une grille de cellules partant d'un état initial ou un certain nombres d'entre elles sont vivantes et les autres mortes. 
Les cellules évoluent selon un pas d'évolution, et à chaque incrémentation de celui-ci peuvent passer de vivantes à mortes et inversement en fonction de l'état des cellules avoisinantes (ou encore d'autres paramètres, comme le temps d'existence de la cellule...).

Dans notre implémentation de base, on définira qu'une cellule reste en vie au pas suivant si elle a exactement 2 ou 3 cellules voisines vivantes, et qu'une cellule morte devient vivante uniquement si elle a 3 voisines vivantes.

Suite à l'implémentation du niveau 2 du jeu, l'implémentation du vieillissement fait que si celui-ci est activé, une cellule meurt si son âge dépasse 8 pas d'évolutions. Les cellules vivantes sont également désormais affichées par leur âge (de 1 à 8), qui reste fixe si le vieillissement est désactivé. Le choix d'avoir un voisinage cyclique ou non cyclique a également été implémenté dans ce niveau.

Lors du niveau 3 du jeu de la vie on a implémenté la possibilité d'avoir des cellules non viables qui ne peuvent à aucun moment devenir vivantes.

Le niveau 4 consistait à implémenter une interface graphique en utilisant la librairie cairo sous Linux et à avoir une compilation séparée par Makefile en fonction d'une variable MODE = TEXTE (ou GRAPHIQUE par défaut).

Le niveau 5 consistait en deux tâches: 
* Compiler la gestion des grilles et du jeu ( grille.h et jeu.h ) séparément comme une bibliothèque nommée libjeu.
* Implémenter un algorithme lancé par la touche 'o' qui permette de détecter une oscillation de l'état de la grille et d'afficher la période de celle-ci le cas échéant.

## Fichiers

#### Sources
* grille.c : Implémentation des fonctions de grille.h
* io.c : Implémentation des fonctions de io.h
* io_cairo.c : Implémentation des fonctions de io_cairo.h
* jeu.c : Implémentation des fonctions de jeu.h
* main.c : Point d'entrée du programme

#### Headers/Include
* grille.h :
Contient la structure grille.
Contient les fonctions permettant de créér, détruire et de modifier les éléments d'une structure de type grille. Les fonctions set_vivante(), set_morte() et est_vivante() sont définies directement dans ce fichier.
* io.h :
Contient les fonctions d'affichage et d'effacement dans le terminal, ainsi que debut_jeu(), fonction qui contient la boucle de jeu du programme permettant de faire évoluer la grille, de choisir les paramètres optionnels activés (vieillissement, voisinage cyclique) ou de choisir une nouvelle grille.
* io_cairo.h :
Contient les fonctions d'affichage utilisant la librairie cairo (en conjonction avec xlib), et la fonction debut_jeu() réimplémentée pour fonctionner spécifiquement avec ces librairies. Contient également la structure layoutState qui regroupe les dimensions pour l'affichage de la grille et de la barre d'états.
* jeu.h :
Contient les fonctions de tests de conditions nécessaires pour déterminer l'évolution d'une cellule, ainsi que la définition de la structure logicState , qui regroupe les données déterminant le mode de fonctionnement du programme (vieillissement, voisinage cyclique ou non) et l'état logique de la grille (nombre de pas d'évolution).
Cette évolution est réalisée par la fonction evolue() se trouvant dans ce fichier.


#### Autres (non documentés)
* Répertoire de fichiers de grilles
* Makefile
* Doxyfile

## Changelog

Le versionnage choisi consiste à donner au minimum un tag de version à chaque révision correspondant à un niveau du jeu (correspondant à chaque séance de TP) implémenté. 

Des tags additionnels seront définis pour les corrections ou améliorations apportées postérieurement à l'implantation du niveau avant le passage au niveau suivant.

### V5.3
* Correction de coquilles et de commentaires

### V5.2
* Amélioration de l'affichage en mode graphique

### V5.1
* Correction du versionnage des tags

### V5.0
* Détection de l'oscillation implémentée avec affichage de sa période
* Amélioration de l'affichage (mode texte et graphique)

### V4.2
* Mise à jour de la documentation

### V4.1
* Création de structures pour l'organisation des données du layout et du mode de fonctionnement du programme

### V4.0
* Affichage graphique de la grilles et du temps d'évolution
* Mise à l'échelle automatique de la grille par rapport à la fenêtre

### V3.1
* Implémentation de la compilation séparée en bibliothèque de jeu.h et grille.h (fait partie des tâches du niveau 5)

### V3.0
* Implémentation des cellules non viables et de leur affichage

### V2.2
* Amélioration de la documentation

### V2.1
* Correction du nom du fichier d'archive
* Amélioration de la documentation

### V2.0
* Passage entre voisinage cyclique/non-cyclique implémenté
* Vieillissement (optionnel) implémenté
* Temps d'évolution global de la grille affiché 

### V1.0
* Documentation Doxygen de base complétée
* Touche n de changement de grille implémentée
* Fonctions alloue_grille() et libere_grille() implémentées

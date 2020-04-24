
/**
 * \file io.h
 * \brief Déclaration des fonctions d'affichage et de gestion d'input.
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <grille.h>
#include <jeu.h>

/**
 * \brief Affichage d'un trait horizontal d'une grille en fonction du nombre de colonnes de celle-ci.
 * \param [in] c Nombre de colonnes
 */
void affiche_trait (int c);

/**
 * \brief Affichage d'une ligne de la grille.
 * \param [in] c Le nombre de colonnes de la grille
 * \param [in] ligne Tableau de cellules de la ligne à afficher.
 */
void affiche_ligne (int c, int* ligne);

/**
 * \brief Affichage d'une grille.
 * \param [in] g La grille que l'on souhaite afficher
 */
void affiche_grille (grille g);

/**
 * \brief Effacement d'une grille.
 */
void efface_grille ();

/**
 * \brief Fonction contenant la boucle de jeu, traite les inputs du joueur.
 * \param [in,out] g La grille du jeu
 * \param [in] gc Une grille de copie temporaire de g lors de chaque évolution
 */
void debut_jeu(grille *g, grille *gc);

#endif

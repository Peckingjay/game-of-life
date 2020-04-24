
/**
 * \file jeu.h
 * \brief Déclaration des fonctions permettant de gérer les cellules et leur évolution.
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/** 
 * \struct logicState
 * \brief Cette structure contient les variables et fonctions déterminant le mode de fonctionnement du programme.
 * \var logicState::tpsEvol
 * tpsEvol correspond au nombre de pas d'évolution de la grille courante.
 * \var logicState::vieillissement
 * vieillissement est un booléen déterminant si le vieillissement des cellules est activé.
 * \var logicState::compte_voisins_vivants
 * compte_voisins_vivants est un pointeur sur la fonction de calcul du voisinage, qui est soit cyclique soit non-cyclique.
 * \var logicState::periodeOsc
 * periodeOsc correspond à la période d'oscillation du programme, si elle a été détectée.
 * \var logicState::lastAction
 * lastAction décrit la dernière action effectuée par le programme.
 */
typedef struct {int tpsEvol;
				int vieillissement;
				int (*compte_voisins_vivants) (int,int, grille);
				int periodeOsc;
				char lastAction[35];} logicState;

/**
 * \brief Initialise la structure contenant l'état logique par défaut du programme: Voisinage cyclique activé, vieillissement désactivé, temps d'évolution à 0.
 * \param [in] lgc Structure contenant l'état logique du programme.
 */
void initLogicState(logicState * lgc);

/**
 * \brief Modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques.
 * \param [in] i Entier dont on souhaite calculer le reste de la division par m
 * \param [in] m Entier par lequel on souhaite diviser
 * \return Reste de la division de i par m
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \brief Décompte du nombre de voisins vivants (cyclique) de la cellule (i,j) les bords sont cycliques.
 * \param [in] i Index de ligne de la cellule dans la grille
 * \param [in] j Index de colonne de la cellule dans la grille
 * \param [in] g Grille sur laquelle on opère
 * \return Nombre de voisins vivants
 */
int compte_voisins_vivants_cycle (int i, int j, grille g);

/**
 * \brief Décompte du nombre de voisins vivants (non-cyclique) de la cellule (i,j) les bords sont cycliques.
 * \param [in] i Index de ligne de la cellule dans la grille
 * \param [in] j Index de colonne de la cellule dans la grille
 * \param [in] g Grille sur laquelle on opère
 * \return Nombre de voisins vivants
 */
int compte_voisins_vivants_no_cycle (int i, int j, grille g);

/**
 * \brief Evolution de la grille g d'un pas de temps.
 * \param [in,out] g La grille du jeu
 * \param [in] gc Une grille de copie temporaire de g lors de chaque évolution
 * \param [in] lgc Contient les données relatives au mode de fonctionnement du programme (vieillissement, calcul du voisinage, temps d'évolution)
 */
void evolue (grille *g, grille *gc,logicState *lgc);

#endif

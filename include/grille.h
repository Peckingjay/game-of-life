
/**
 * \file grille.h
 * \brief Déclaration des fonctions permettant de gérer la structure des grilles.
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** 
 * \struct grille
 * \brief Cette structure contient un tableau de cellules avec son nombre de lignes et colonnes.
 * \var grille::nbl
 * nbl correspond au nombre de lignes de la grille.
 * \var grille::nbc
 * nbc correspond au nombre de colonnes de la grille.
 * \var grille::cellules
 * cellules est la matrice 2-dimensionnelle contenant l'état des cellules. 
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/** 
 * \brief Alloue une grille de taille l*c, et initialise toutes ses cellules à mortes.
 * \param [in] l Nombre de lignes pour la grille
 * \param [in] c Nombre de colonnes pour la grille
 * \param [out] g La grille à allouer
 */
void alloue_grille (int l, int c, grille* g);

/** 
 * \brief Libère l'espace mémoire alloué à une grille
 * \param [in] g La grille à libérer.
 */
void libere_grille (grille* g);

/**
 * \brief Alloue et initalise la grille g à partir d'un fichier.
 * \param [in] filename Chemin d'accès au fichier contenant la grille à initialiser
 * \param [out] g La grille à initialiser
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * \brief Rend vivante la cellule (i,j) de la grille g.
 * \param [in] i Index de ligne de la cellule dans la grille
 * \param [in] j Index de colonne de la cellule dans la grille
 * \param [out] g La grille que l'on souhaite modifier
 */
static inline void set_vivante(int i, int j, grille g){ if (g.cellules[i][j] != -1) g.cellules[i][j] = 1;}

/**
 * \brief Rend morte la cellule (i,j) de la grille g.
 * \param [in] i Index de ligne de la cellule dans la grille
 * \param [in] j Index de colonne de la cellule dans la grille
 * \param [out] g La grille que l'on souhaite modifier
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * \brief Rend non viable la cellule (i,j) de la grille g.
 * \param [in] i Index de ligne de la cellule dans la grille
 * \param [in] j Index de colonne de la cellule dans la grille
 * \param [out] g La grille que l'on souhaite modifier
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * \brief Teste si la cellule (i,j) de la grille g est vivante.
 * \param [in] i Index de ligne de la cellule dans la grille
 * \param [in] j Index de colonne de la cellule dans la grille
 * \return Booléen valant vrai si la cellule est vivante.
 * \param [in] g La grille que l'on souhaite tester
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

/**
 * \brief Recopie de la grille gs dans gd (sans allocation).
 * \param [in] gs La grille que l'on souhaite copier
 * \param [out] gd La grille ou l'on stocke la copie
 */
void copie_grille (grille gs, grille gd);

#endif

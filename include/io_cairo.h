
/**
 * \file io_cairo.h
 * \brief Déclaration des fonctions d'affichage et de gestion d'input (version interface graphique avec cairo).
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h> 

#include <grille.h>
#include <jeu.h>

/** 
 * \struct layoutState
 * \brief Cette structure contient les dimensions principales nécessaires à l'affichage du layout
 * \var layoutState::largeurCase
 * largeurCase correspond à la largeur d'une case de la grille.
 * \var layoutState::hauteurCase
 * hauteurCase correspond à la hauteur d'une case de la grille.
 * \var layoutState::tailleBarre
 * tailleBarre correspond à la hauteur de la barre d'affichage en bas de l'écran.
 * \var layoutState::gridW
 * gridW correspond à la largeur de la grille.
 * \var layoutState::gridH
 * gridH correspond à la hauteur de la grille.
 */
typedef struct {double largeurCase;
				double hauteurCase;
				double tailleBarre;
				double gridW;
				double gridH;} layoutState;

/**
 * \brief Retourne un layout en fonction de la taille de la fenêtre et des dimensions de la grille.
 * \param [in] winWidth Largeur de la fênetre.
 * \param [in] winHeight Hauteur de la fenêtre.
 * \param [in] nbColonnes Le nombre de colonnes de la grille.
 * \param [in] nbLignes Le nombre de lignes de la grille.
 * \return Le layout contenant les dimensions correctes.
 */
layoutState initLayoutState(int winWidth, int winHeight, int nbColonnes, int nbLignes);

/**
 * \brief Affichage d'un rectangle arrondi pour une cellule.
 * \param [in] cr Le masque cairo pour les fonctions d'affichage.
 * \param [in] x La position en abscisse x où afficher le rectangle.
 * \param [in] y La position en ordonnée y où afficher le rectangle.
 * \param [in] width La largeur du rectangle.
 * \param [in] height La hauteur du rectangle.
 */
void cairo_curved_cell(cairo_t *cr,double x,double y, double width, double height);

/**
 * \brief Affichage d'une grille.
 * \param [in] g La grille que l'on souhaite afficher
 * \param [in] surface La surface cairo utilisée pour créer le masque d'affichage.
 * \param [in] lt Le layout contenant les dimensions pour l'affichage.
 */
void affiche_grille (grille g,cairo_surface_t *surface,layoutState lt);

/**
 * \brief Affichage de la barre d'état du jeu (en bas de la fenêtre).
 * \param [in] surface La surface cairo utilisée pour créer le masque d'affichage.
 * \param [in] lt Le layout contenant les dimensions pour l'affichage.
 * \param [in] lgc Contient les données relatives au mode de fonctionnement du programme (vieillissement, calcul du voisinage, temps d'évolution)
 */
void affiche_barre_etat (cairo_surface_t *surface, layoutState lt, logicState *lgc);

/**
 * \brief Fonction contenant la boucle de jeu, traite les inputs du joueur.
 * \param [in,out] g La grille du jeu
 * \param [in] gc Une grille de copie temporaire de g lors de chaque évolution
 */
void debut_jeu(grille *g, grille *gc);

#endif

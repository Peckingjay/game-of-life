
/**
 * \file jeu.c
 * \brief Implémentation des fonctions gérant les cellules et leur évolution
 */

#include "jeu.h"

int compte_voisins_vivants_cycle (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

//On teste si le voisin ne se trouve pas de sur un bord opposé avant chaque incrémentation
int compte_voisins_vivants_no_cycle (int i, int j, grille g)
{
	int v = 0, l=g.nbl, c = g.nbc;
	if (i>0)
	{
		if (j>0)	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
		v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
		if (j<c)	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	}
	if (j>0)	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	if (j<c)	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	if (i < l)
	{
		if (j>0)	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
		v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
		if (j<c)	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	}
	return v; 
}

void initLogicState(logicState * lgc)
{
	lgc->tpsEvol = 0;
	lgc->compte_voisins_vivants = &compte_voisins_vivants_cycle;
	lgc->vieillissement = 0;
	lgc->periodeOsc = -1;
	snprintf(lgc->lastAction,35,"> Grille initialisée");
}

void evolue (grille *g, grille *gc,logicState *lgc){
	copie_grille (*g,*gc); // Copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (*lgc->compte_voisins_vivants) (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // Evolution d'une cellule vivante
				
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
				
				//Si le vieillissement est actif on effectue les opérations nécessaires.
				else if (lgc->vieillissement == 1)
				{ 
					if (g->cellules[i][j] < 8)
					g->cellules[i][j] += 1;
					else set_morte(i,j,*g);
				}
			}
			else 
			{ // Evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}


/**
 * \file io.c
 * \brief Implémentation des fonctions d'affichage et de gestion d'input
 */
 
#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
	{
		if (ligne[i] == 0 ) 
			printf ("|   ");
		else if (ligne[i] == -1 ) 
			printf ("| X ");
		else printf ("| %i ",ligne[i]);
	}
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (){
	//Utilisation des codes d'échappement ANSI pour effacer dans le terminal.
	printf("\e[1;1H\e[2J"); 
}

void debut_jeu(grille *g, grille *gc){
	
	efface_grille();
	
	printf("Temps d'evolution: 0, Oscillation: Inconnue");
	affiche_grille(*g);
	
	//Initialisation des données déterminant le mode de fonctionnement du programme
	logicState lgc;
	initLogicState(&lgc);
	printf(lgc.lastAction);
	
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,&lgc);
				lgc.tpsEvol++;
				if (lgc.tpsEvol == 1)
				{snprintf(lgc.lastAction,35,"> Evolution\n");}
				efface_grille();
				printf("Temps d'evolution: %i",lgc.tpsEvol);
				if (lgc.periodeOsc == -1)
				{printf(" | Oscillation: Inconnue");}
				else if (lgc.periodeOsc == 1)
				{printf(" | Oscillation: Etat stable");}
				else
				{printf(" | Oscillation: Période de %i",lgc.periodeOsc);}
				affiche_grille(*g);
				printf(lgc.lastAction);
				snprintf(lgc.lastAction,35,"> Evolution\n");
				break;
			}
			
			case 'n' : 
			{ // touche "n" pour entrer nom d'une nouvelle grille
				
				libere_grille(g);
				libere_grille(gc);
				
				char grille[256];
				printf("> Veuillez entrer le nom de la nouvelle grille (chemin inclus):");
				scanf("%s", grille);
				
				init_grille_from_file(grille,g);
				alloue_grille (g->nbl, g->nbc, gc);
				initLogicState(&lgc);
				
				efface_grille();
				printf("Temps d'evolution: %i",lgc.tpsEvol);
				affiche_grille(*g);
				snprintf(lgc.lastAction,35,"> Nouvelle grille chargée\n");
				break;
			}
			
			case 'c' : 
			{ // touche "c" pour activer/désactiver le voisinage cyclique
				if (lgc.compte_voisins_vivants == &compte_voisins_vivants_cycle)
				{
					lgc.compte_voisins_vivants = &compte_voisins_vivants_no_cycle;
					snprintf(lgc.lastAction,35,"> Voisinage cyclique désactivé");
				}
				else
				{
					lgc.compte_voisins_vivants = &compte_voisins_vivants_cycle;
					snprintf(lgc.lastAction,35,"> Voisinage cyclique activé\n");
				}
				printf("\n\e[1A");
				break;
			}
			
			case 'v' : 
			{ // touche "v" pour activer/désactiver le vieillissement
				if (lgc.vieillissement == 1)
				{
					lgc.vieillissement = 0;
					snprintf(lgc.lastAction,35,"> Vieillissement désactivé\n");
				}
				else
				{
					lgc.vieillissement = 1;
					snprintf(lgc.lastAction,35,"> Vieillissement activé\n");
				}
				printf("\n\e[1A");
				break;
			}
			case 'o':
			{
				// touche "o" pour détecter l'oscillation
				if (lgc.periodeOsc != -1)
					snprintf(lgc.lastAction,35,"> Oscillation déjà détectée\n");
				else
				{
					//Créer une nouvelle grille T à partir de la grille actuelle
					grille *t;
					t = malloc(sizeof(grille));
					alloue_grille (g->nbl, g->nbc, t);
					copie_grille (*g,*t);
					
					//Créer un tableau de 1000 pointeurs de grille
					grille *tabEtats[1000];
	
					int flagPeriode=0,i,j,k,l;
					
					for (i=0; i<1000 && flagPeriode !=1; i++)
					{
					//Stocker l'état de T dans le tableau
						tabEtats[i] = malloc(sizeof(grille));
						alloue_grille (g->nbl, g->nbc, tabEtats[i]);
						copie_grille (*t,*tabEtats[i]);
					
					//On parcourt le tableau d'états précédents en sens inverse
						for (l = i-1; l >= 0 && flagPeriode != 1; l--)
						{
							//On teste si les deux grilles sont identiques
							flagPeriode = 1;
							for (j=0; j<t->nbl; j++)
							{
								for (k=0; k<t->nbc && flagPeriode != 0; ++k)
								{
									if (t->cellules[j][k] != tabEtats[l]->cellules[j][k])
									{
										flagPeriode = 0;
									}
								}
							}
						}
						//Si une oscillation ou état stable a été détecté(e)
						if (flagPeriode == 1)
						{
							//Une valeur de 1 pour i-l indique un état stable;
							lgc.periodeOsc = i-l-1;
						}
						else
						{
							evolue(t,gc,&lgc);
						}
					}
					//On libère les pointeurs de grille que l'on a assignés.
					for (l = 0; l<i ; l++)
					{
						libere_grille(tabEtats[l]);
					}
					libere_grille(t);
				}
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}

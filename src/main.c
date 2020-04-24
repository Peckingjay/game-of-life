
/**
 * \file main.c
 * \brief Gère le déroulement global du programme.
 */
#include <stdio.h>

#include <grille.h>
#include "io.h"
#include <jeu.h>

/**
 * \brief Fonction main, point d'entrée de l'application.
 * \param [in] argc Nombre de chaînes de caractères passées en paramètre au programme
 * \param [in] argv Tableau de chaînes de caractères passées en paramètre au programme (argv[0] contient le nom du programme)
 * \return Status Code d'erreur. 0 pour exécution correcte.
 */
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}


/**
 * \file test.c
 * \brief Teste le bon fonctionnement du programme.
 */
#include <stdio.h>
#include <assert.h>

#include <grille.h>
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

	grille g;
	init_grille_from_file("grilles/grille1.txt",&g);


	//TESTS
	assert(g.cellules[0][0] == 0);
	assert(g.cellules[1][2] == 1);
	assert(g.cellules[1][3] == 1);
	//fprint
	
	libere_grille(&g);
	return 0;
}

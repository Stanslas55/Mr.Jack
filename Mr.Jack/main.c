#include "Structures.h"
#include "Jeu.h"
#include "Utils.h"
#include "Affichage.h"

int main() {
	srand((unsigned int) time(NULL));
	Jeu *jeu = Initialisation();	
	int tour = 0, test = 0;
	int pions[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	while (1) {		

		test = Tour_de_jeu(jeu, tour, pions);
		tour++;

		if (Fin(jeu, tour) == 1 || test == 1) break;		
	}
	printf("Partie finie en %d tours\n", tour);
	
	Liberer_jeu(jeu);
	system("pause");
	return 0;
}
#include "Affichage.h"

void Affiche_positions(Jeu* jeu) {

	for (int i = 0; i < 8; i++) Affiche_position(jeu, i);	
}

void Affiche_position(Jeu* jeu, int i) {
	
	printf("Pion %d en position [%d|%d]\n", i, jeu->positions[i]->y, jeu->positions[i]->x);	
}
// Perso = -2, Rien = -1, Sortie = 0, Mur = 1, Lampe = 2
void Affiche_case(Case *C) {

	switch (C->objet)
	{
	case Perso: // Perso
		printf("%d", C->perso->numero);
		break;
	case Rien:
		printf(" ");
		break;
	case Sortie:
		printf("S");
		break;
	case Mur:
		printf("X");
		break;
	case Lampe:
		printf("L");
		break;
	}
}

void Affiche_plateau(Jeu* jeu) {

	printf("\n");
	for (int i = 0; i < 7; i++) printf("--");
	printf("\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 13; j++) {
			Affiche_case(jeu->grille[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 7; i++) printf("--");
	printf("\n\n");
}

void Affiche_carac_perso(Personnage* P) {

	printf("[%d %d %d]\n", P->perso, P->suspect, P->visible);
}

void Verifier_cases(Jeu* jeu) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 13; j++) {
			if (jeu->grille[i][j]->objet == Perso) {
				Affiche_carac_perso(jeu->grille[i][j]->perso);
			}
		}
	}
}
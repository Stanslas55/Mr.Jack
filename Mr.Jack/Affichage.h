// Ce fichier contient les fonctions relatives � l'affichage du jeu, et au debug.
#include "Jeu.h"

void Affiche_positions(Jeu* jeu); // Affiche les positions des pions.

void Affiche_position(Jeu* jeu, int i); // Affiche la position d'un pion.

void Affiche_case(Case* C); // Affiche une case.

void Affiche_plateau(Jeu* jeu); // Affiche le plateau de jeu.

void Affiche_carac_perso(Personnage* P); // Affiche les donn�es de la variable P.

void Verifier_cases(Jeu* jeu); // Verifier que les personnages sont bien plac�s, et affiche toutes les caracteristiques.
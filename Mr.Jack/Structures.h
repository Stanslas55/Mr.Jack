// Ce fichier contient les structures nécéssaires au jeu.
#ifndef STRUCTURES_H
#define STRUCTURES_H

enum objets { Perso = -2, Rien = -1, Sortie = 0, Mur = 1, Lampe = 2 }; // Liste des objets disponibles sur une case.
enum etats { Suspect = 1, Innocent = 2, Jack = 3, Autre = 4, Visible = 1, Invisible = 0 };

typedef struct Personnage {

	int numero; // Indique le numéro du personnage : [1, 8].
	int perso; // Indique si le personnage est Jack ou Autre: [3, 4].
	int suspect; // Indique si le personnage est suspect ou innocent : [1, 2].
	int visible; // Indique si le personnage est visible ou non [1, 0].
	int visible_avant;
	
}Personnage;

typedef struct Case {

	Personnage *perso; // Personnage présent sur la case.
	int objet;  // Contiendra une valeur de l'enumération d'objets.
}Case;

typedef struct Coordonnees {
	int y; // Indique la coordonnée en y du joueur.
	int x; // Indique la coordonnée en x du joueur.
	
}Coordonnees;



typedef struct Jeu {
	Case *grille[8][13]; // Tableau de cases
	Coordonnees *positions[8]; // [0, 7].
	int numero_jack; // [1, 8] Contiendra la numero de jack (pion X dans la liste des pions).
}Jeu;
#endif // !STRUCTURES_H
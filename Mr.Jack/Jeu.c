#define _CRT_SECURE_NO_WARNINGS

#include "Jeu.h"

Jeu *Initialisation(){
	Jeu *jeu = (Jeu*)malloc(1 * sizeof(Jeu));	
	
	FILE *fichier = NULL;
	char symbole;
	int i, j, compteur_perso = 1;

	for (i = 0; i < 8; i++){
		jeu->positions[i] = (Coordonnees*)malloc(1 * sizeof(Coordonnees));
		for (j = 0; j < 13; j++){
			jeu->grille[i][j] = (Case*)malloc(1 * sizeof(Case));
			jeu->grille[i][j]->perso = (Personnage*)malloc(1 * sizeof(Personnage));			// -> raccourcis de *grille[i][j].perso
		}
	}
	i = 0, j = 0;
	fichier = fopen("Plateau.txt", "r");

	if (fichier == NULL){
		printf("Erreur lors de l\'ouverture du fichier !\n");
		return NULL;
	}	
	while (fscanf(fichier, "%c", &symbole) != EOF) {
		
		switch (symbole){

		case 'X':
			
			jeu->grille[i][j]->objet = Mur;
			j++;
			break;
		case 'S':
			
			jeu->grille[i][j]->objet = Sortie;
			j++;
			break;
		case 'O': // C'est un personnage.
			
			jeu->grille[i][j]->perso->numero = compteur_perso;
			jeu->grille[i][j]->perso->perso = Autre;
			jeu->grille[i][j]->perso->suspect = Suspect; // Les personnages sont tous suspects de base.	

			jeu->grille[i][j]->perso->visible = 0;
			jeu->grille[i][j]->perso->visible_avant = 0;

			jeu->grille[i][j]->objet = Perso; // L'objet contenu est un perso.
			
			jeu->positions[compteur_perso - 1]->x = j; // Les coordonnées dans le tableau.
			jeu->positions[compteur_perso - 1]->y = i;

			j++, compteur_perso++;
			break;
		case ' ':
			
			jeu->grille[i][j]->objet = Rien;
			j++;
			break;
		case 'L':
			
			jeu->grille[i][j]->objet = Lampe;
			j++;
			break;
		case '\n':
			
			i++, j = 0;
			break;		
		}
	}	
	jeu->numero_jack = rand() % (8 - 1) + 1; // Generer un nombre entre A et B : rand() % (B - A) + A;
	printf("Le message suivant n\'est destine qu\'a Jack !!\n");
	system("pause");
	printf("Jack est le pion %d\n", jeu->numero_jack);
	system("pause");
	system("cls");
	return jeu;
}

void Liberer_jeu(Jeu *jeu){

	for (int i = 0; i < 8; i++){

		free(jeu->positions[i]);
		for (int j = 0; j < 13; j++){

			free(jeu->grille[i][j]->perso);
			free(jeu->grille[i][j]);			
		}
	}
	free(jeu);
}

int Fin(Jeu *jeu, int tour) {

	if (tour == 8) return 1;

	int y = jeu->positions[jeu->numero_jack - 1]->y;
	int x = jeu->positions[jeu->numero_jack - 1]->x;

	if ((x == 1 && y == 0) || (x == 11 && y == 0) || (x == 1 && y == 7) || (x == 11 && y == 7)) {
		if (jeu->grille[jeu->positions[jeu->numero_jack - 1]->y][jeu->positions[jeu->numero_jack - 1]->x]->perso->visible_avant == 0) {
			return 1;
		}
	}
	return 0;
}

int Tour_de_jeu(Jeu *jeu, int tour, int pioche[8]) {

	int choix[8] = { -1, -1, -1, -1, -1, -1, -1, -1 }, i = 0, decision, visible;
	printf("Tour %d\n", tour + 1);
	printf("Personnages innocents : ");
	for (int j = 0; j < 8; j++) {
		if (jeu->grille[jeu->positions[j]->y][jeu->positions[j]->x]->perso->suspect == Innocent) {
			printf("%d ", j + 1);
		}
	}
	printf("\n");
	Affiche_plateau(jeu);
	//printf("Position de Jack : \n");
	//Affiche_position(jeu, jeu->numero_jack - 1);
	if (tour % 2 == 0) { // Si le tour est pair.

		Melanger(pioche);
		decision = Demande("Inspecteur", 4, choix, pioche) - 1; // -1 Pour correspondre aux entrées du tableau de pions.
		Jouer(jeu, Autre, pioche[decision]);
		decision = Demande("Jack", 4, choix, pioche) - 1;
		Jouer(jeu, Jack, pioche[decision]);
		decision = Demande("Jack", 4, choix, pioche) - 1;
		Jouer(jeu, Jack, pioche[decision]);
		decision = Demande("Inspecteur", 4, choix, pioche) - 1;
		Jouer(jeu, Autre, pioche[decision]);
	}
	else 	{ // Sinon il est impair.
		decision = Demande("Jack", 8, choix, pioche) - 1;		
		Jouer(jeu, Jack, pioche[decision]);
		decision = Demande("Inspecteur", 8, choix, pioche) - 1;
		Jouer(jeu, Autre, pioche[decision]);
		decision = Demande("Inspecteur", 8, choix, pioche) - 1;
		Jouer(jeu, Autre, pioche[decision]);
		decision = Demande("Jack", 8, choix, pioche) - 1;
		Jouer(jeu, Jack, pioche[decision]);
	}
	if (Pion_Visible(jeu, jeu->positions[jeu->numero_jack - 1]) == 1) {
		printf("Jack est visible\n");
		visible = 1;		// visible = 1 -> visible.
	}
	else {
		printf("Jack n'est pas visible\n");
		visible = 0; // visible = 0 -> invisible.
	}
	jeu->grille[jeu->positions[jeu->numero_jack - 1]->y][jeu->positions[jeu->numero_jack - 1]->x]->perso->visible_avant = jeu->grille[jeu->positions[jeu->numero_jack - 1]->y][jeu->positions[jeu->numero_jack - 1]->x]->perso->visible;
	// jeu->grille[ position y de jack][position x de jack] -> visible avant
	for (int j = 0; j < 8; j++) {
		jeu->grille[jeu->positions[j]->y][jeu->positions[j]->x]->perso->visible = Pion_Visible(jeu, jeu->positions[j]);
		if (jeu->grille[jeu->positions[j]->y][jeu->positions[j]->x]->perso->visible != visible) {
			jeu->grille[jeu->positions[j]->y][jeu->positions[j]->x]->perso->suspect = Innocent;
		}
	}
	Eteindre_Lampe(jeu, tour + 1);
	return 0; // Par defaut, le jeu n'est pas fini.
}

int Bon(int choix, int depart, int tab[8]) {

	if (choix <= depart || choix > depart + 4) {	// Verifier qu'on est bien dans les bornes du tableau.
		return 0;
	}
	if (tab[choix - 1] != -1) { 	// Verifier que la carte n'a pas été jouée.
		return 0; 
	}
	return 1;
}

int Demande(char* nom, int borne, int choix[8], int pioche[8]) {

	int i = borne - 4, decision;
	do {
		printf("%s, choisissez un numero de joueur parmis ceux proposes : ", nom);
		while (i != borne) {
			if (choix[i] == -1) {
				printf("(%d) %d ", i + 1, pioche[i]);
			}
			i++;
		}
		printf("\nchoix ? : ");
		scanf("%d", &decision);
		getchar();
	} while (Bon(decision, borne - 4, choix) == 0);
	printf("Vous avez choisi le joueur %d\n", pioche[decision - 1]);
	choix[decision - 1] = 1;
	return decision;
}

int Pion_Visible(Jeu *jeu, Coordonnees* pos) {

	for (int y = -1; y < 2; y++) {
		for (int x = -1; x < 2; x++) {

			if (pos->x + x > 0 && pos->x + x < 13 && pos->y + y > 0 && pos->y + y < 8) {
				if (x == 0 && y == 0) continue; // Pour éviter de tester la case de (pos).
				// Si autour de la case courante se trouve un Pion ou une Lampe, le personnage est visible.
				if (jeu->grille[pos->y + y][pos->x + x]->objet == Lampe || jeu->grille[pos->y + y][pos->x + x]->objet == Perso) return 1;				
			}
		}
	}
	return 0;
}

void Eteindre_Lampe(Jeu *jeu, int tour) {

	if(tour == 1) jeu->grille[5][1]->objet = Mur;
	if(tour == 2) jeu->grille[2][11]->objet = Mur;
	if(tour == 3) jeu->grille[1][2]->objet = Mur;
	if(tour == 4) jeu->grille[5][10]->objet = Mur;	
}

void Jouer(Jeu *jeu, int joueur, int pion) {

	char choix;
	for (int i = 0; i < 3; i++) {
		do {			
			printf("Il vous reste %d mouvements, dans quelle direction voulez vous aller ? (H B G D (S pour passer)) : ", 3 - i);
			scanf("%c", &choix);
			getchar();
		} while (Coup_Valide(jeu, pion - 1, choix, joueur) == 0);
		Affiche_plateau(jeu);		
	}
}
// pion : indice du joueur dans le tableau.
// joueur : jack ou autre.
int Coup_Valide(Jeu* jeu, int pion, char choix, int joueur) {

	Coordonnees *coords = jeu->positions[pion];
	if (choix == 'B' || choix == 'b') {
		if (coords->y + 1 < 8) {
			if (jeu->grille[coords->y + 1][coords->x]->objet == Sortie && pion + 1 == jeu->numero_jack && jeu->grille[coords->y][coords->x]->perso->visible_avant == 1)
				return 0;
			if (jeu->grille[coords->y + 1][coords->x]->objet == Rien) {					

				jeu->grille[coords->y + 1][coords->x]->perso = jeu->grille[coords->y][coords->x]->perso; // On déplace le perso de case.
				jeu->grille[coords->y + 1][coords->x]->objet = Perso; // On rempli le tag objet, pour préciser que cette case contient désormais un perso.
				
				jeu->grille[coords->y][coords->x]->objet = Rien; // L'ancienne case ne contient plus de perso.
				jeu->grille[coords->y][coords->x]->perso = NULL; // On supprime le perso.

				jeu->positions[pion]->y++; // Mettre à jour les coordonnées.
				return 1;
			}
			if (jeu->grille[coords->y + 1][coords->x]->objet == Perso && joueur == Autre) {
				if (jeu->grille[coords->y + 1][coords->x]->perso->numero == jeu->numero_jack) {
					printf("L'enqueteur decouvre Jack ! Felicitations\nLa partie est terminee.\n");
					system("pause");
					exit(0);
				}
				else {
					printf("L'enqueteur lance une accusation a tors ! Jack profite de la panique pour fuir et gagne la partie !\n");
					system("pause");
					exit(0);
				}
			}
			if (jeu->grille[coords->y + 1][coords->x]->objet == Perso && joueur == Jack) return 0;					
		}
	}
	if (choix == 'H' || choix == 'h') {
		if (coords->y - 1 >= 0) {
			if (jeu->grille[coords->y - 1][coords->x]->objet == Sortie && pion + 1 == jeu->numero_jack && jeu->grille[coords->y][coords->x]->perso->visible_avant == 1)
				return 0;
			if (jeu->grille[coords->y - 1][coords->x]->objet == Rien || jeu->grille[coords->y - 1][coords->x]->objet == Sortie) {

				jeu->grille[coords->y - 1][coords->x]->perso = jeu->grille[coords->y][coords->x]->perso; 
				jeu->grille[coords->y - 1][coords->x]->objet = Perso; 

				jeu->grille[coords->y][coords->x]->objet = Rien; 
				jeu->grille[coords->y][coords->x]->perso = NULL; 

				jeu->positions[pion]->y--; 
				return 1;
			}
			if (jeu->grille[coords->y - 1][coords->x]->objet == Perso && joueur == Autre) {
				if (jeu->grille[coords->y - 1][coords->x]->perso->numero == jeu->numero_jack) {
					printf("L'enqueteur decouvre Jack ! Felicitations\nLa partie est terminee.\n");
					system("pause");
					exit(0);
				}
				else {
					printf("L'enqueteur lance une accusation a tors ! Jack profite de la panique pour fuir et gagne la partie !\n");
					system("pause");
					exit(0);
				}
			}
			if (jeu->grille[coords->y - 1][coords->x]->objet == Perso && joueur == Jack) return 0;						
		}
	}
	if (choix == 'G' || choix == 'g') {
		if (coords->x - 1 >= 0) {
			if (jeu->grille[coords->y][coords->x - 1]->objet == Rien || jeu->grille[coords->y][coords->x - 1]->objet == Sortie) {

				jeu->grille[coords->y][coords->x - 1]->perso = jeu->grille[coords->y][coords->x]->perso; 
				jeu->grille[coords->y][coords->x - 1]->objet = Perso; 

				jeu->grille[coords->y][coords->x]->objet = Rien; 
				jeu->grille[coords->y][coords->x]->perso = NULL;	

				jeu->positions[pion]->x--;
				return 1;
			}
			if (jeu->grille[coords->y][coords->x - 1]->objet == Perso && joueur == Autre) {
				if (jeu->grille[coords->y][coords->x - 1]->perso->numero == jeu->numero_jack) {
					printf("L'enqueteur decouvre Jack ! Felicitations\nLa partie est terminee.\n");
					system("pause");
					exit(0);
				}
				else {
					printf("L'enqueteur lance une accusation a tors ! Jack profite de la panique pour fuir et gagne la partie !\n");
					system("pause");
					exit(0);
				}
			}
			if (jeu->grille[coords->y][coords->x - 1]->objet == Perso && joueur == Jack) return 0;					
		}
	}
	if (choix == 'D' || choix == 'd') {
		if (coords->x + 1 < 13) {
			if (jeu->grille[coords->y][coords->x + 1]->objet == Rien || jeu->grille[coords->y][coords->x + 1]->objet == Sortie) {

				jeu->grille[coords->y][coords->x + 1]->perso = jeu->grille[coords->y][coords->x]->perso; 
				jeu->grille[coords->y][coords->x + 1]->objet = Perso; 

				jeu->grille[coords->y][coords->x]->objet = Rien; 
				jeu->grille[coords->y][coords->x]->perso = NULL; 

				jeu->positions[pion]->x++; 
				return 1;
			}
			if (jeu->grille[coords->y][coords->x + 1]->objet == Perso && joueur == Autre) {
				if (jeu->grille[coords->y][coords->x + 1]->perso->numero == jeu->numero_jack) {
					printf("L'enqueteur decouvre Jack ! Felicitations\nLa partie est terminee.\n");
					system("pause");
					exit(0);
				}
				else {
					printf("L'enqueteur lance une accusation a tors ! Jack profite de la panique pour fuir et gagne la partie !\n");
					system("pause");
					exit(0);
				}
			}
			if (jeu->grille[coords->y][coords->x + 1]->objet == Perso && joueur == Jack) return 0;			
		}
	}
	if (choix == 'S' || choix == 's') return 1;
	return 0;
}
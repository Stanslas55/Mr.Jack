// Ce fichier contient les fonctions relatives au fonctionnement du jeu.
#ifndef JEU_H
#define JEU_H
#include "Structures.h"
#include "Affichage.h"
#include "Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Jeu *Initialisation(); // Initialise et renvoie le plateau de jeu.

void Liberer_jeu(Jeu *jeu); // Libère la mémoire.

int Fin(Jeu *jeu, int tour); // Dit si le jeu est fini ou non.

int Tour_de_jeu(Jeu *jeu, int tour, int pioche[8]); // Realise un tour de jeu.

int Bon(int choix, int depart, int tab[8]); // Dis si une entrée choix est bonne par rapport à certaines conditions.

int Demande(char* nom, int borne, int choix[8], int pioche[8]); // Demande le choix d'un pion à jouer.

int Pion_Visible(Jeu *jeu, Coordonnees* pos); // Renvoie 1 si le pion est visible, 0 sinon.

void Eteindre_Lampe(Jeu *jeu, int tour); // Eteint les lampes en fonction du tour de jeu.

void Jouer(Jeu *jeu, int joueur, int pion); // Permet au joueur de deplacer son pion.

int Coup_Valide(Jeu *jeu, int pion, char choix, int joueur); // Verifie que le coup à jouer est possible.



#endif // !JEU_H

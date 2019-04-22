#include "Utils.h"

void Melanger(int Perso[8]){
	int j, tmp;	

	for (j = 0; j < 8; j++) printf("[%d]", Perso[j]);
	printf("\n");

	for (int i = 1; i < 8; i++)
	{
		j = rand() % (i + 0) + 0; // indexe aléatoire entre 0 et i.		
		
		tmp = Perso[i];
		Perso[i] = Perso[j];
		Perso[j] = tmp;
	}
	for (j = 0; j < 8; j++) printf("[%d]", Perso[j]);
	printf("\n");
}
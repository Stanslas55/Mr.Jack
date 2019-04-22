// Ce fichier contient les constantes et macro relatives à la lisibilité du code.
#ifndef UTILS_H
#define UTILS_H

#define DEBUG 0
#if DEBUG
#include "vld.h"
#endif // DEBUG

#include <stdlib.h>

void Melanger(int Perso[8]); // A tester, sinon passer par adresse.

#endif // !UTILS_H


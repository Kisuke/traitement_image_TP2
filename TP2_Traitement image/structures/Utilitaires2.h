#ifndef UTILITAIRES2_H_INCLUDED
#define UTILITAIRES2_H_INCLUDED

#include "Utilitaires1.h"
#include "Structures.h"
#include "LibMedian.h"
#include "LibMoyen.h"
#include "Seuillage.h"
#include "Erosion.h"
#include "Dilatation.h"

#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>


int Accueil(IMAGE **, IMAGE **, FILE **, FILE **, short *, short *, unsigned char *);
void Traitement(IMAGE **, IMAGE **, int);
int securite(int, int);
void Initialisation_avec_vois(IMAGE **, IMAGE **, POINT **, POINT **);
void Initialisation_sans_vois(IMAGE **, IMAGE **, POINT **);

#endif // UTILITAIRES2_H_INCLUDED

/* --------------------------------------------------*/
/*   Filtrage Moyen				     */
/*   Fichier: LibMoyen.c			     */
/*   Auteur: Patrick Bonnin			     */
/*   Date de Creation:                               */
/*   Livree : Le TI a l'IUT                          */
/* --------------------------------------------------*/
#include "Structures.h"
/* ---- Code de l'operateur Moyen ---- */

void FiltrageMoyen(IMAGE *image, IMAGE *imres)
{
  POINT	*point = NULL, *pointv=NULL; /* point courant et point voisin */
  short	i,j; /* variables indices ligne et colonne du voisinage */
  short	moy; /* variable temporaire de type short */

    Initialisation_avec_vois(&image, &imres, &point, &pointv);

/* --- Balayage Video de l'image
   sauf premieres et dernieres lignes et colonnes --- */

  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image) - 1;
           POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image) - 1;
           POINT_X(point)++)
  {
    moy = 0;	/* initialisation de la variable temporaire */

/* --- Balayage Video du voisinage 3x3 --- */
    for(j = 0; j < 3; j++)
    for(i = 0; i < 3; i++)
    {
      /* calcul des coordonnees absolues du point voisin */
      POINT_X(pointv) = POINT_X(point) + i - 1;
      POINT_Y(pointv) = POINT_Y(point) + j - 1;

      moy += (short)PIXEL(image, pointv);

    } /* --- fin du balayage du voisinage --- */
    moy /= 9;/* la division se fait a la fin ! */

    PIXEL(imres, point) = (unsigned char)moy;
  }/* --- fin du balayage de l'image --- */

  free((void *)pointv);/* --- liberation des zones memoire */
  free((void *)point);
} /* --- fin de l'operateur --- */

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

  if(crea_POINT(point) == NULL) /* creation des points */
  {
     fprintf(stderr,"Erreur d'Allocation Memoire du Point : Moyen \n");
     exit (0);
  }

  if(crea_POINT(pointv) == NULL)
  {
     fprintf(stderr,"Erreur d'Allocation Memoire du Point Voisin : Moyen \n");
     exit (0);
  }


/* --- Initialisation des Bords :
   on recopie l'image originale --- */
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image);
           POINT_X(point)++)
  {
    POINT_Y(point) = 0; /* premiere ligne */
    PIXEL(imres, point) = PIXEL(image, point);

    POINT_Y(point) = NLIG(image) - 1;/* derniere ligne */
    PIXEL(imres, point) = PIXEL(image, point);
  } /*--- fin recopiage 1er et derniere ligne --- */

  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image);
           POINT_Y(point)++)
  {
    POINT_X(point) = 0;/* premiere colonne */
    PIXEL(imres, point) = PIXEL(image, point);

    POINT_X(point) = NCOL(image) - 1;/* derniere colonne */
    PIXEL(imres, point) = PIXEL(image, point);

  } /*--- fin recopiage 1er et derniere colonne --- */

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

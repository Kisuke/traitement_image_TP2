/* --------------------------------------------------*/
/*   Filtrage Moyen				     */
/*   Fichier: LibMoyen.c			     */
/*   Auteur: Patrick Bonnin			     */
/*   Date de Creation:                               */
/*   Livree : Le TI a l'IUT                          */
/* --------------------------------------------------*/
#include "Structures.h"
/* ---- Code de l'operateur Moyen ---- */

void FiltrageMedian(IMAGE *image, IMAGE *imres)
{
  POINT	*point = NULL, *pointv=NULL; /* point courant et point voisin */
  short	i,j, x, y; /* variables indices ligne et colonne du voisinage */
  short	min; /* variable temporaire de type short */
  short tab_val[9];
  int num_tab;
  int finished = 1;

  Initialisation_avec_vois(&image, &imres, &point, &pointv);

/* --- Balayage Video de l'image
   sauf premieres et dernieres lignes et colonnes --- */


  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image) - 1;
           POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image) - 1;
           POINT_X(point)++)
  {
    min = 255;	/* initialisation de la variable temporaire */
    num_tab = 0;
/* --- Balayage Video du voisinage 3x3 --- */
    for(j = 0; j < 3; j++)
    for(i = 0; i < 3; i++)
    {
      /* calcul des coordonnees absolues du point voisin */
      POINT_X(pointv) = POINT_X(point) + i - 1;
      POINT_Y(pointv) = POINT_Y(point) + j - 1;
      //Stockage de la valeur du pixel
        tab_val[num_tab] = PIXEL(image,pointv);
        num_tab++;
    }
     /* --- fin du balayage du voisinage --- */
    /* Réorganisation des valeurs par ordre croissant */
    finished = 1;
      while (finished)
      {
          finished = 0;
          for(x=0;x<9-1;x++)
          {
              if(tab_val[x] > tab_val[x+1])
              {
                  min = tab_val[x+1];
                  tab_val[x+1] = tab_val[x];
                  tab_val[x] = min;
                  finished = 1;
              }
          }
      }
      PIXEL(imres,point) = tab_val[5]; //Récupération de la médiane
  }/* --- fin du balayage de l'image --- */

  free((void *)pointv);/* --- liberation des zones memoire */
  free((void *)point);
} /* --- fin de l'operateur --- */

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
  POINT	*point = NULL, *pointv=NULL, *pointvv=NULL; /* point courant et point voisin */
  short	i,j, x, y; /* variables indices ligne et colonne du voisinage */
  short	min; /* variable temporaire de type short */
  short tab_val[9];
  int num_tab;
  int finished = 1;

  if(crea_POINT(point) == NULL) /* creation des points */
  {
     fprintf(stderr,"Erreur d'Allocation Memoire du Point : Median \n");
     exit (0);
  }

  if(crea_POINT(pointv) == NULL)
  {
     fprintf(stderr,"Erreur d'Allocation Memoire du Point Voisin : Median \n");
     exit (0);
  }

if(crea_POINT(pointvv) == NULL)
  {
     fprintf(stderr,"Erreur d'Allocation Memoire du Point Voisin suivant : Median \n");
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
  free((void *)pointvv);
} /* --- fin de l'operateur --- */

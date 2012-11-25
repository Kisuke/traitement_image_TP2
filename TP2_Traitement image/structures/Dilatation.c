#include "Dilatation.h"
void Dilatation(IMAGE *image, IMAGE *imres)
{
 POINT	*point = NULL, *pointv=NULL, *pointvv=NULL; /* point courant et point voisin */
  short	i,j,dilate; /* variables indices ligne et colonne du voisinage */

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

  }

  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image)-1; POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image)-1; POINT_X(point)++)
  {

      //PIXEL(imres,point) = PIXEL(image,point) < seuil? (short)0 : (short)255;
      dilate = 0;
      /* --- Balayage Video du voisinage 3x3 --- */
    for(j = 0; j < 3; j++)
    for(i = 0; i < 3; i++)
    {
      /* calcul des coordonnees absolues du point voisin */
      POINT_X(pointv) = POINT_X(point) + i - 1;
      POINT_Y(pointv) = POINT_Y(point) + j - 1;
      //Vérification du point voisin
        if(PIXEL(image,pointv) > 128) dilate = 1; //Si un point voisin est blanc, il y'a dilatation
    }
     /* --- fin du balayage du voisinage --- */
     PIXEL(imres,point) = dilate?0:PIXEL(image,point);

  }

}

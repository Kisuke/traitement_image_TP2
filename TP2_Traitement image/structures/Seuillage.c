#include "Seuillage.h"
void Seuillage(IMAGE *image, IMAGE *imres, int seuil)
{
 POINT	*point = NULL, *pointv=NULL, *pointvv=NULL; /* point courant et point voisin */
  short	i,j; /* variables indices ligne et colonne du voisinage */

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

  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); POINT_X(point)++)
  {

      PIXEL(imres,point) = PIXEL(image,point) < seuil? (short)0 : (short)255;
  }
}

#include "Erosion.h"
void Erosion(IMAGE *image, IMAGE *imres)
{
 POINT	*point = NULL, *pointv=NULL; /* point courant et point voisin */
  short	i,j, erode; /* variables indices ligne et colonne du voisinage */

    Initialisation_avec_vois(&image, &imres, &point, &pointv);

  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image)-1; POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image)-1; POINT_X(point)++)
  {

      //PIXEL(imres,point) = PIXEL(image,point) < seuil? (short)0 : (short)255;
      erode = 0;
      /* --- Balayage Video du voisinage 3x3 --- */
    for(j = 0; j < 3; j++)
    for(i = 0; i < 3; i++)
    {
      /* calcul des coordonnees absolues du point voisin */
      POINT_X(pointv) = POINT_X(point) + i - 1;
      POINT_Y(pointv) = POINT_Y(point) + j - 1;
      //Vérification du point voisin
        if(PIXEL(image,pointv) < 128) erode = 1; //Si un point voisin est noir, le pixel est erodé
    }
     /* --- fin du balayage du voisinage --- */
     PIXEL(imres,point) = erode?0:PIXEL(image,point);

  }

}

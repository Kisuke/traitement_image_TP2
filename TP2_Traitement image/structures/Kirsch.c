#include "Kirsch.h"

void Kirsch(IMAGE *image, IMAGE *imres)
{
    POINT	*point = NULL, *pointv=NULL; /* point courant et point voisin */
  short	i,j,gradh,, gradv, var_tab[9], cpt; /* variables indices ligne et colonne du voisinage */
  float vecteur1, vecteur2, vecteur3;

    Initialisation_avec_vois(&image, &image, &point, &pointv);

  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image)-1; POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image)-1; POINT_X(point)++)
  {

      //PIXEL(imres,point) = PIXEL(image,point) < seuil? (short)0 : (short)255;
      gradh = 0, gradv =0, cpt = 0;
      /* --- Balayage Video du voisinage 3x3 --- */
    for(j = 0; j < 3; j++)
    for(i = 0; i < 3; i++)
    {
      /* calcul des coordonnees absolues du point voisin */
      POINT_X(pointv) = POINT_X(point) + i - 1;
      POINT_Y(pointv) = POINT_Y(point) + j - 1;
      //Enregistrement du point voisin

      var_tab[cpt] = PIXEL(image,pointv);
      cpt++;

    }
     /* --- fin du balayage du voisinage --- */

     //Cas de vérification verticale :
     vecteur1 = abs(5*var_tab[2]-3*var_tab[0]-3*var_tab[1]);
     vecteur2 = abs(5*var_tab[5]-3*var_tab[3]);
     vecteur3 = abs(5*var_tab[8]-3*var_tab[6]-3*var_tab[7]);
     gradv = (vecteur1+vecteur2+vecteur3)/15;
}

#include "Seuillage.h"
void Seuillage(IMAGE *image, IMAGE *imres, int seuil)
{
 POINT	*point = NULL;

 Initialisation_sans_vois(&image, &imres, &point);

  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); POINT_X(point)++)
  {

      PIXEL(imres,point) = PIXEL(image,point) < seuil? NOIR: BLANC;
  }
}

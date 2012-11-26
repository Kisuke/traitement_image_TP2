/* ----------------------------------------------------*/
/*   Programme Principal de Lissage Moyen	       */
/*   Fichier: Moyen.c				       */
/*   Auteur: Patrick Bonnin			       */
/*   Date de Creation:		                       */
/* ----------------------------------------------------*/
#include "structures/Structures.h"
#include "structures/Utilitaires1.h"
#include "structures/Utilitaires2.h"
#include <string.h>
#include <conio.h>
main(int argc, char **argv)
{
  IMAGE	    *image = NULL,*imres = NULL;
  short	    nlig, ncol, choix;
  unsigned char	prof = 1;
  FILE	    *fichier = NULL, *fichres = NULL;

  /* --- USAGE --- */
  if(argc != 3)
  {
    choix = Accueil(&image, &imres, &fichier, &fichres, &nlig, &ncol, &prof);
  }
    Traitement(&image,&imres, choix);

/* --- Enregistrement de l'Image Resultat --- */
  fprintf(fichres,"P5\n%d %d\n255\n",(int)ncol, (int)nlig);
  EnregistreImage(fichres, imres);

/* --- Liberation de l'Image --- */
  Libere_Image(image);
  Libere_Image(imres);
  fprintf(stderr,"Fin du traitement d'image\n");
  getch();
}

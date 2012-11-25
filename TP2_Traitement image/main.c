/* ----------------------------------------------------*/
/*   Programme Principal de Lissage Moyen	       */
/*   Fichier: Moyen.c				       */
/*   Auteur: Patrick Bonnin			       */
/*   Date de Creation:		                       */
/* ----------------------------------------------------*/
#include "structures/Structures.h"
#include "structures/Utilitaires1.h"
#include "structures/LibMedian.h"
#include "structures/LibMoyen.h"
#include "structures/Seuillage.h"
#include "structures/Erosion.h"
#include <string.h>
#include <conio.h>
main(int argc, char **argv)
{
  IMAGE	    *image = NULL,*imres = NULL;
  short	    nlig, ncol;
  unsigned char	prof = 1;
  FILE	    *fichier = NULL, *fichres = NULL;
    char nomfichier[30];
    char nomretour[30];
  /* --- USAGE --- */
  if(argc != 3)
  {
fprintf(stderr,"USAGE : Lissage median image immoy \n");
fprintf(stderr,"image : nom de l'image a lisser \n");
fprintf(stderr,"image : image mediane  \n");
fprintf(stderr,"Effectue le lissage median de l'image source \n");
    scanf("%s",nomfichier);

    //exit(0);
  }
/* --- Image Source --- */

  if(!(fichier = fopen(nomfichier,"rb")))
  {
fprintf(stderr,"ouverture du fichier Image %s impossible\n",*argv);
    exit(0);
  }

/* --- Image Resultat --- */
  if(!(fichres = fopen("retour.pgm","wb")))
  {
fprintf(stderr,"ouverture du fichier Image Resultat %s impossible\n",*argv);
    exit(0);
  }
/* --- Recuperation de la Taille de l'Image --- */
   Lecture_EntetePGM(fichier, &ncol, &nlig);
   fprintf(stderr, "Taille de l'Image %d lignes x %d colonnes\n", nlig,ncol);

/* --- Creation des Images --- */
  if (crea_IMAGE(image) == NULL)	/* creation de la structure image */
  {
    fprintf(stderr,"Erreur d'Allocation Memoire Structure Image : Moyen \n");
    exit (0);
  }
  Creation_Image (image, &nlig, &ncol, &prof);

  if (crea_IMAGE(imres) == NULL) /* creation de la structure image resultat */
  {
fprintf(stderr,"Erreur d'Allocation Memoire Structure Image Resultat: Moyen \n");
    exit (0);
  }
  Creation_Image (imres, &nlig, &ncol, &prof);

/* --- Lecture du Fichier Image et
   Remplissage du champ de Donnees --- */
  Lecture_Image(fichier,image);

/* --- Lissage Médian --- */
    //FiltrageMoyen( image, imres)
    //FiltrageMedian (image, imres);
    //Seuillage(image,imres,128)
    Erosion(image,imres);

/* --- Enregistrement de l'Image Resultat --- */
  fprintf(fichres,"P5\n%d %d\n255\n",(int)ncol, (int)nlig);
  EnregistreImage(fichres, imres);

/* --- Liberation de l'Image --- */
  Libere_Image(image);
  Libere_Image(imres);
  fprintf(stderr,"Fin de l'Operateur Moyen\n");
  getch();
}

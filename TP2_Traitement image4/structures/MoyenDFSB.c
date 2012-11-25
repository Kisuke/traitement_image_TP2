/* ----------------------------------------------------*/
/*   Programme Principal de Lissage Moyen	       */
/*   en implantation Acces Sequentiel des Pixels       */
/*   sans traitement des bords de l'image              */
/*   Fichier: MoyenDFSB.c			       */
/*   Auteur: Patrick Bonnin			       */
/*   Date de Modification : Octobre 2000               */
/* ----------------------------------------------------*/

#include "Structures.h"
#include "Utilitaires1.h"
#include "LibMoyenDFSB.h"

main(int argc, char **argv)

{
  IMAGE	    *image = NULL,*imres = NULL;
  short	    nlig, ncol;
  unsigned char	prof = 1;
  FILE	    *fichier = NULL, *fichres = NULL;


  /* --- USAGE --- */
  if(argc != 3)
  {
fprintf(stderr,"USAGE : MoyenDFSB image immoy \n");
fprintf(stderr,"image : nom de l'image a lisser \n");
fprintf(stderr,"immoy : image moyennee \n");
fprintf(stderr,"Effectue le lissage moyen de l'image source : \n");
fprintf(stderr,"Implantation en Acces Sequentiel aux Pixels \n");
fprintf(stderr,"sans traiter les bords \n");
    exit(0);
  }

/* --- Image Source --- */

  if(!(fichier = fopen(*++argv,"r+")))
  {
fprintf(stderr,"ouverture du fichier Image %s impossible\n",*argv);
    exit(0);
  }

/* --- Recuperation de la Taille de l'Image --- */
   Lecture_EntetePGM(fichier, &ncol, &nlig);
   fprintf(stderr, "Taille de l'Image %d lignes x %d colonnes\n", nlig,ncol);

/* --- Image Resultat --- */
  if(!(fichres = fopen(*++argv,"w")))
  {
fprintf(stderr,"ouverture du fichier Image Resultat %s impossible\n",*argv);
    exit(0);
  }

/* --- Creation des Images --- */
  if(crea_IMAGE(image) == NULL)	/* creation de la structure image */
  {
     fprintf(stderr,"Erreur lors de la creation de la structure image \n");
  }
  Creation_Image (image, &nlig, &ncol, &prof);

  if(crea_IMAGE(imres) == NULL)	/* creation de la structure image  resultat */
  {
     fprintf(stderr,"Erreur lors de la creation de la structure image \n");
  }
  Creation_Image (imres, &nlig, &ncol, &prof);

/* --- Lecture du Fichier Image et 
   Remplissage du champ de Donnees --- */
  Lecture_Image(fichier,image);

/* --- Lissage Moyen  --- */
  MoyenFlotdeDonneesSB(image, imres); 

/* --- Enregistrement de l'Image Resultat --- */
  fprintf(fichres,"P5\n%d %d\n255\n",(int)ncol, (int)nlig); 
  EnregistreImage(fichres, imres);

/* --- Liberation de l'Image --- */
  Libere_Image(image);
  Libere_Image(imres);	
}

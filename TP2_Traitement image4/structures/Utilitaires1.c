/* -----------------------------------------------------------*/
/*  Fonctions de Lecture, Ecriture, et Creation d'Images      */
/*  Environnement Restreint pour TP d'Etudiants               */
/*  sous GCC / Linux                                          */
/*  Fichier: Utilitaires1.c				      */
/*  Auteur: Patrick Bonnin				      */
/*  Modification : Date : Octobre 2000                        */
/* -----------------------------------------------------------*/
#include "Structures.h"

//    --- Programmes de la librairie Utilitaires1.h:
//   void Creation_Image (IMAGE *image,short *pnlig, short *pncol,
//				unsigned char *pprof
//   Role : Cree :  - la structure image
//		    - le tableau de pixels
//
//   void Libere_Image(IMAGE *image)
//   Role  : Liberer la memoire de l'image allouee dynamiquement
//
//   void Lecture_Image(FILE *fichier, IMAGE *image)
//   Role  : Lecture d'une Image dans un fichier et remplissage
//		   du champ de donnees
//
//   void EnregistreImage (FILE *fichier, IMAGE *image)
//   Role  : Enregistre l'image dans le fichier
//
//   void Conversion_Image(IMAGE *image, IMAGE *imcoul)
//   Role : Converti l'Image Noir et Blanc dans une Image Couleur
//
//   void Inversion(IMAGE *image, IMAGE *imres)
//   Role : Inverse une Image
//
//   void Lecture_EntetePGM(FILE *fichier, short *pncol, short *nlig)
//   Role  : Lecture d'une entete .PGM d'une Image N&B dans un fichier
//         : et remplissage du nombre de ligne et de colonnes
//
//   void Lecture_EntetePPM(FILE *fichier, short *pncol, short *pnlig)
//   Role  : Lecture d'une entete .PPM d'une Image couleur dans un fichier
//         : et remplissage du nombre de ligne et de colonnes
//
//   Modifications  : Ludovic RAULET : Possibilite d'avoir un commentaire
//	   : avant ou apres le nombre de lignes et colonnes pour
//	   : la lecture des images .PGM et PPM
//
/* ---------------------------------------------------------------------- */
/* --- Creation de la Structure de Donnees Image --- */
void Creation_Image (IMAGE *image, short *pnlig, short *pncol,
       unsigned char *pprof)
{
/* Test de Reussite de l'Allocation Memoire */
  if (image == NULL)
  {
     fprintf(stderr,"Struture Image non Allouee : Creation_Image \n");
     exit(0);
  }

  NLIG(image) = *pnlig; /* remplissage des divers champs */
  NCOL(image) = *pncol;
  PROF(image) = *pprof;

 /* ---Creation du Tableau de Pixel constituant
               les donnees de l'image--- */
  switch (*pprof)
  {
      case 1: /* Image classique Noir et Blanc sur un Octet */
   PIOCTET(image) = (unsigned char *)MALLOC(
     (long)NLIG(image)*(long)NCOL(image)* sizeof(unsigned char));

   /* Test de Reussite de l'Allocation Memoire */
   if (PIOCTET(image) == NULL)
   {
     fprintf(stderr,"Memoire non Allouee : Creation_Image \n");
     exit(0);
   }
   break;

     case 2: /* image des etiquettes */
   PIETIQ(image) = (unsigned short int *)MALLOC(
    (long)NLIG(image)*(long)NCOL(image)* sizeof(unsigned short));

   /* Test de Reussite de l'Allocation Memoire */
   if (PIETIQ(image) == NULL)
   {
     fprintf(stderr,"Memoire non Allouee : Creation_Image \n");
     exit(0);
   }
   break;

     case 3: /* Image Couleur sur 3 Octets: R,V,B */
   PIOCTET(image) = (unsigned char *)MALLOC(
     3*(long)NLIG(image)*(long)NCOL(image)* sizeof(char));

   /* Test de Reussite de l'Allocation Memoire */
   if (PIOCTET(image) == NULL)
   {
     fprintf(stderr,"Memoire non Allouee : Creation_Image \n");
     exit(0);
   }
   break;

     case 4: /* Image des Differences */
   PISUB(image) = (short int *)MALLOC(
     (long)NLIG(image)*(long)NCOL(image)* sizeof(short int));

   /* Test de Reussite de l'Allocation Memoire */
   if (PISUB(image) == NULL)
   {
     fprintf(stderr,"Memoire non Allouee : Creation_Image \n");
     exit(0);
   }
   break;

     default: /* type inexistant */
       fprintf(stderr,"Type d'Image Inexistant dans cette version : Creation_Image \n");
       exit(0);
       break;
  }

} /* --- fin --- */

/*----------------------------------------------------------*/
/*      Liberation en memoire du tableau de pixels          */
/*      et de la structure                                  */

void Libere_Image(IMAGE *image)

{
   switch(PROF(image))	/* liberation du tableau de pixels */
   {
       case 1: /* Image classique Noir et Blanc sur un Octet */
       case 3: /* Image Couleur sur 3 Octets: R,V,B */
	 FREE(PIOCTET(image));
         break;

       case 2: /* image des Etiquettes */
	 FREE(PIETIQ(image));
         break;

       case 4: /* Image des Differences */
	 FREE(PISUB(image));
         break;

       default:
	 fprintf(stderr,"Erreur de Profondeur \n");
	 fprintf(stderr,"Programme Libere_Image \n");
	 exit(0);
         break;
   }

   free((void *)image);
}
/*---------------------------------------------------------*/
void Lecture_Image(FILE *fichier, IMAGE *image)

{
  switch(PROF(image))
  {
      case 1:
	fread(PIOCTET(image),sizeof(unsigned char),
           (long)NLIG(image) * (long)NCOL(image),fichier);
	break;

      case 2:
	fread(PIETIQ(image),sizeof(short),
           (long)NLIG(image) * (long)NCOL(image),fichier);
	break;

      case 3:
	fread(PIOCTET(image),sizeof(unsigned char),
	   3 * (long)NLIG(image) * (long)NCOL(image),fichier);
	break;

      default:
	fprintf(stderr,"Type non existant \n");
	exit(0);
	break;
  } /* fin du switch */

} /* --- fin Lecture_Image --- */

/*------------------------------------------------------*/
void EnregistreImage (FILE *fichier, IMAGE *image)

{
  switch(PROF(image))
  {
       case 1:
	 fwrite(PIOCTET(image),sizeof(unsigned char),
	    (long)NLIG(image) * (long)NCOL(image),fichier);
	 break;

       case 2:
         fwrite(PIETIQ(image),sizeof(short),
	    (long)NLIG(image) * (long)NCOL(image),fichier);
	  break;

       case 3:
         fwrite(PIOCTET(image),sizeof(unsigned char),
	    3 * (long)NLIG(image) * (long)NCOL(image),fichier);
	 break;

       default:
	 fprintf(stderr,"Type non existant \n");
	 exit(0);
	 break;
  } /* fin du switch */
} /* --- fin de l'enregistrement de l'Image --- */

/*-------------------------------------------------------*/
void Conversion_Image(IMAGE *image, IMAGE *imcoul)

{
  POINT	*point = NULL;

  if(crea_POINT(point) == NULL)
  {
  fprintf(stderr,"Erreur d'Allocation Memoire pour le point \n");
    exit(0);
  }

  for (POINT_Y(point) = 0; POINT_Y(point) < NLIG(image);
	    POINT_Y(point)++)
  for (POINT_X(point) = 0; POINT_X(point) < NCOL(image);
	    POINT_X(point)++)
  {
    PIXEL_R(imcoul,point) = PIXEL(image,point);
    PIXEL_V(imcoul,point) = PIXEL(image,point);
    PIXEL_B(imcoul,point) = PIXEL(image,point);
  }
  free((void *)point);
}

/*--------------------------------------------------------*/
Inversion (IMAGE *imsrc, IMAGE *imres)
{
   POINT *point = NULL;

   if(crea_POINT(point) == NULL)
   {
 fprintf(stderr,"Erreur d'Allocation Memoire pour le Point : Inversion \n");
      exit(0);
   }

   for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(imsrc);
	    POINT_Y(point)++)
   for(POINT_X(point) = 0; POINT_X(point) < NCOL(imsrc);
            POINT_X(point)++)
     PIXEL(imres, point) = 255 - PIXEL(imsrc, point);

   free((void *)point);
} /* fin de l'inversion d'une image */
/*--------------------------------------------------------*/

//////////////////////////////////////////////////////////////
/* ---------- Nouvelles Versions Lecture PGM -------------- */
//////////////////////////////////////////////////////////////
void Lecture_EntetePGM(FILE *fichier, short *pncol, short *pnlig)
{
 char entete[20];
 int  i;

 fread(entete,4,1,fichier); // Lire l'entete "P5" & le debut du commentaire '#'
 if ((entete[0] != 'P') || (entete[1] !='5'))
 {
   fprintf(stderr,"Le Fichier n'est pas PGM \n");
   exit(0);
 }

 if (entete[3]=='#')      // si il y a un commentaire alors ->
   {
    while(entete[0]!=0x0A)     // passer le commentaire ...
    {
     fread(entete,1,1,fichier);
    }
    i=0;
   }
 else 	// sinon (donnée 'largeur' & 'longueur' déjà présente
   {
    entete[0]=entete[3];
    i=1;
   }
 fread(&entete[i],1,1,fichier);

 while(entete[i]!=0x0A)     // lire la largeur * longueur
   {
    i++;
    fread(&entete[i],1,1,fichier);
    if (entete[i]==' ') entete[i]=0x00;
   }
 *pncol=atoi(entete);
 entete[i]=0x00;
 *pnlig=atoi(&entete[strlen(entete)+1]);

fread(entete,1,1,fichier);
 if (entete[0]=='#')      // si il y a un deuxième commentaire alors ->
   {
   while(entete[0]!=0x0A)     // on passe ce commentaire
     {
     fread(entete,1,1,fichier);
     i++;
     }
   }
fread(entete,1,1,fichier);
 while(entete[0]!=0x0A)     // passer la resolution
     {
     fread(entete,1,1,fichier);
     i++;
     }
 // a la fin de cette serie de manipulation
 // le pointeur FILE se situe sur les donnees ...
} // fin de lecture entete PGM

/* ---------- Nouvelles Versions Lecture PPM -------------- */

void Lecture_EntetePPM(FILE *fichier, short *pncol, short *pnlig)
{
 char entete[20];
 int  i;

 fread(entete,4,1,fichier); // Lire l'entete "P6" & le debut du commentaire '#'
 if ((entete[0] != 'P') || (entete[1] !='6'))
 {
   fprintf(stderr,"Le Fichier n'est pas PPM \n");
   exit(0);
 }

 if (entete[3]=='#')      // si il y a un commentaire alors ->
   {
    while(entete[0]!=0x0A)     // passer le commentaire ...
    {
     fread(entete,1,1,fichier);
    }
    i=0;
   }
 else 	// sinon (donnée 'largeur' & 'longueur' déjà présente
   {
    entete[0]=entete[3];
    i=1;
   }
 fread(&entete[i],1,1,fichier);

 while(entete[i]!=0x0A)     // lire la largeur * longueur
   {
    i++;
    fread(&entete[i],1,1,fichier);
    if (entete[i]==' ') entete[i]=0x00;
   }
 *pncol=atoi(entete);
 entete[i]=0x00;
 *pnlig=atoi(&entete[strlen(entete)+1]);


fread(entete,1,1,fichier);
 if (entete[0]=='#')      // si il y a un deuxième commentaire alors ->
   {
   while(entete[0]!=0x0A)     // on passe ce commentaire
     {
     fread(entete,1,1,fichier);
     i++;
     }
   }
fread(entete,1,1,fichier);
 while(entete[0]!=0x0A)     // passer la resolution
     {
     fread(entete,1,1,fichier);
     i++;
     }
 // a la fin de cette serie de manipulation
 // le pointeur FILE se situe sur les donnees ...
} // fin de lecture entete PPM








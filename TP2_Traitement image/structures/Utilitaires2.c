#include "Utilitaires2.h"

int Accueil(IMAGE **image, IMAGE **imres, FILE **fichier, FILE **fichres, short *nlig, short *ncol, unsigned char *prof)
{
    char nomfichier[30];
    char nomretour[30];
    char *point = NULL;
    int choix = 0, cpt, cpt2;


    fprintf(stderr,"TP1 - Introduction aux Traitements d'image \n");
    fprintf(stderr,"Srikanth Ramanoudjame - Hermann Sidibe \n\n");
    fprintf(stderr,"Nom de l'image :  \n");

    scanf("%s",nomfichier);

    fprintf(stderr,"\n Choix d'un traitement d'image : \n\n");
    fprintf(stderr,"1 - Seuillage ( noir/blanc ) \n2 - Filtrage Moyen \n3 - Filtrage Median \n4 - Erosion \n5 - Dilatation \n6 - Ouverture \n7 - Fermeture \n8 - Detection de contours \n");

    choix = securite(0,0);


        /* --- Image Source --- */

      if(!(*fichier = fopen(nomfichier,"rb")))
      {
    fprintf(stderr,"ouverture du fichier Image impossible\n");
        exit(0);
      }

      point = strrchr(nomfichier,46); //Recherche l'emplacement du point
      if(point)
      {
          for(cpt = 0; &nomfichier[cpt] != point;cpt++)
          {
          }
          strncpy(nomretour,nomfichier,cpt);
          nomretour[cpt]= '\0';
        switch(choix)
            {
                case 1: strcat(nomretour,"_SeuilRetour"); break;
                case 2: strcat(nomretour,"_MoyenRetour"); break;
                case 3: strcat(nomretour,"_MediaRetour"); break;
                case 4: strcat(nomretour,"_ErosiRetour"); break;
                case 5: strcat(nomretour,"_DilatRetour"); break;
                case 6: strcat(nomretour,"_OuverRetour"); break;
                case 7: strcat(nomretour,"_FermeRetour"); break;
                case 8: strcat(nomretour,"_GradiRetour"); break;
                default: strcat(nomretour,"_ndef_retour"); break;
            }

          printf("%s",nomretour);
          for(cpt2=cpt;nomfichier[cpt2] != '\0';cpt2++) //Copie de l'extension de l'image
          {
              nomretour[cpt2+12] = nomfichier[cpt2];
          }
          nomretour[cpt2+12] = '\0';

      }else strcat(nomretour,"retour");

    /* --- Image Resultat --- */
      if(!(*fichres = fopen(nomretour,"wb")))
      {
    fprintf(stderr,"ouverture du fichier Image Resultat impossible\n");
        exit(0);
      }
    /* --- Recuperation de la Taille de l'Image --- */
       Lecture_EntetePGM(*fichier, ncol, nlig);
       fprintf(stderr, "Taille de l'Image %d lignes x %d colonnes\n", *nlig,*ncol);

    /* --- Creation des Images --- */
      if (crea_IMAGE(*image) == NULL)	/* creation de la structure image */
      {
        fprintf(stderr,"Erreur d'Allocation Memoire Structure Image : Moyen \n");
        exit (0);
      }
      Creation_Image (*image, nlig, ncol, prof);

      if (crea_IMAGE(*imres) == NULL) /* creation de la structure image resultat */
      {
        fprintf(stderr,"Erreur d'Allocation Memoire Structure Image Resultat: Moyen \n");
        exit (0);
      }
      Creation_Image (*imres, nlig, ncol, prof);

    /* --- Lecture du Fichier Image et
       Remplissage du champ de Donnees --- */
      Lecture_Image(*fichier,*image);
      return choix;

}

void Traitement(IMAGE **image,IMAGE **imres,int choix)
{
    int val;
    switch(choix)
    {
        case 1:
            fprintf(stderr,"\nOperation choisie : Seuillage \n");
            fprintf(stderr,"Veuillez entrer la valeur du seuillage (0 a 255)\n");
            val = securite(0,255);
            Seuillage(*image, *imres, val);
        break;
        case 2:
            fprintf(stderr,"\nOperation choisie : Filtrage Moyen \n");
            FiltrageMoyen(*image, *imres);
        break;
        case 3:
            fprintf(stderr,"\nOperation choisie : Filtrage Median \n");
            FiltrageMedian(*image, *imres);
        break;
        case 4:
            fprintf(stderr,"\nOperation choisie : Erosion \n");
            Erosion(*image, *imres);
        break;
        case 5:

        break;
        case 6:

        break;
        case 7:

        break;
        case 8:

        break;
        default:

        break;
    }
}


void Initialisation_avec_vois(IMAGE **image, IMAGE **imres, POINT **point, POINT **pointv)
{
        if(crea_POINT(*point) == NULL) /* creation des points */
      {
         fprintf(stderr,"Erreur d'Allocation Memoire du Point : Moyen \n");
         exit (0);
      }

      if(crea_POINT(*pointv) == NULL)
      {
         fprintf(stderr,"Erreur d'Allocation Memoire du Point Voisin : Moyen \n");
         exit (0);
      }


    /* --- Initialisation des Bords :
       on recopie l'image originale --- */
      for(POINT_X(*point) = 0; POINT_X(*point) < NCOL(*image);POINT_X(*point)++)
      {
        POINT_Y(*point) = 0; /* premiere ligne */
        PIXEL(*imres, *point) = PIXEL(*image, *point);

        POINT_Y(*point) = NLIG(*image) - 1;/* derniere ligne */
        PIXEL(*imres, *point) = PIXEL(*image, *point);
      } /*--- fin recopiage 1er et derniere ligne --- */

      for(POINT_Y(*point) = 0; POINT_Y(*point) < NLIG(*image);POINT_Y(*point)++)
      {
        POINT_X(*point) = 0;/* premiere colonne */
        PIXEL(*imres, *point) = PIXEL(*image, *point);

        POINT_X(*point) = NCOL(*image) - 1;/* derniere colonne */
        PIXEL(*imres, *point) = PIXEL(*image, *point);

      } /*--- fin recopiage 1er et derniere colonne --- */

}


void Initialisation_sans_vois(IMAGE **image, IMAGE **imres, POINT **point)
{
        if(crea_POINT(*point) == NULL) /* creation des points */
      {
         fprintf(stderr,"Erreur d'Allocation Memoire du Point : Moyen \n");
         exit (0);
      }

}

int securite( int borne_min, int borne_max)
{
    int valeur = 0;
    int verif = 0;
    fflush(stdin);
    verif = scanf("%d", &valeur);
    while(!verif)
    {
        fprintf(stderr,"\n Erreur de saisie : \n");
        verif = scanf("%d", &valeur);
    }
    if(borne_min || borne_max)
    {
        while(valeur < borne_min || valeur > borne_max)
        {
            fprintf(stderr,"\n Erreur, valeur en dehors des bornes : \n");
            verif = scanf("%d", &valeur);
        }
    }
    return valeur;
}

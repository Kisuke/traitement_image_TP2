/* --------------------------------------------------*/
/*   Filtrage Moyen en Implantation Flot de Donnees  */
/*   sans tenir compte des bords                     */ 
/*   Fichier: LibMoyenDFSB.c			     */
/*   Auteur: Patrick Bonnin			     */
/*   Date de Creation:                               */
/*   Livre  : Le TI a l'IUT                          */
/* --------------------------------------------------*/
#include "Structures.h"
/* ---- Code de l'operateur Moyen ---- */

void MoyenFlotdeDonneesSB(IMAGE *imsrc, IMAGE *imres)

{
   unsigned char *ptcsrc; /* pointeur sur point courant image source */ 
   unsigned char *ptcres; /* pointeur sur point courant image resultat */
   
   unsigned char *ptv0src; /* pointeurs sur les points du voisinage */
   unsigned char *ptv1src; /* de l'imaage source */
   unsigned char *ptv2src;
   unsigned char *ptv3src;
   unsigned char *ptv4src;
   unsigned char *ptv5src;
   unsigned char *ptv6src;
   unsigned char *ptv7src;

   short n, m;  /* indices */
   int somme;

/* --- Operateur sur l'Interieur de l'Image --- */ 
/* --- Initialisation du premier point --- */
//   ptcsrc = pdtsrc + lncol + 1;
//   ptcres = pdtres + lncol + 1;

   ptcsrc = imsrc->ptdata.poctet + (long)NCOL(imsrc) + 1;
   ptcres = imres->ptdata.poctet + (long)NCOL(imsrc) + 1;
   
   ptv0src = ptcsrc + 1;
   ptv4src = ptcsrc - 1;

   ptv2src = ptcsrc - (long)NCOL(imsrc);
   ptv1src = ptv2src + 1;
   ptv3src = ptv2src - 1;

   ptv6src = ptcsrc + (long)NCOL(imsrc);
   ptv7src = ptv6src + 1;
   ptv5src = ptv6src - 1;

   for (m = 0; m < NLIG(imsrc) - 2; m++) /* boucle externe sur les lignes */
   {
      for (n = 0; n < NCOL(imsrc) - 2; n++) /* boucle interne sur les colonnes */
      {
	 somme = (int)(*ptcsrc);
	 somme += (int)(*ptv0src);
	 somme += (int)(*ptv1src);
	 somme += (int)(*ptv2src);
	 somme += (int)(*ptv3src);
	 somme += (int)(*ptv4src);
	 somme += (int)(*ptv5src);
	 somme += (int)(*ptv6src);
	 somme += (int)(*ptv7src);
 
         somme /= 9;
	 *ptcres = (unsigned char)somme; /* enregistrement du resultat */

	 /* mise a jour des pointeurs */
	 ptcsrc++;
	 ptcres++;
	 ptv0src++;
	 ptv1src++;
	 ptv2src++;
	 ptv3src++;
	 ptv4src++;
	 ptv5src++;
	 ptv6src++;
	 ptv7src++;

      } /* fin boucle interne sur les colonnes */
      /* mise a jour des pointeurs */
      ptcsrc += 2;
      ptcres += 2;
      ptv0src += 2;
      ptv1src += 2;
      ptv2src += 2;
      ptv3src += 2;
      ptv4src += 2;
      ptv5src += 2;
      ptv6src += 2;
      ptv7src += 2;
   } /* fin boucle externe sur les lignes */  


} /* --- fin de l'operateur --- */   









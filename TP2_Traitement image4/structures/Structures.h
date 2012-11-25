/* -----------------------------------------------------------*/
/*	 Structures et Macros pour le Traitement d'Image      */
/*       Environnement Restreint pour TP d'Etudiants          */
/*       sous GCC / Linux                                     */
/*	 Fichier: Structures.c				      */
/*	 Auteur: Patrick Bonnin				      */
/*	 Date: Modification : Octobre 2000 		      */
/* -----------------------------------------------------------*/
#ifndef _Struct
#define _Struct
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE    1
#define FALSE   0

#define	ABS(X) (((X) > 0) ? (X) : -(X)
#define SIGN(X) (((X) > 0) ? 1 : (((X) < 0) ? -1 : 0 )) 
#define MIN(X,Y) (((X) > (Y)) ? (Y) : (X))
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))

#define MALLOC(XX) malloc(XX)
#define FREE(XX) free(XX)

/* --- Union Donnees Images ou Masque --- */

union pdata
{
  unsigned char   *poctet; /* donnee d'image 8 bits */
  unsigned short  *petiq; /* donnee d'image etiquette */
  short  	  *psubim; /* pour effectuer des differences */
  float 	  *preel; /* pour la structure de masque */
};

typedef union pdata PDATA;

/* ---	Structure Image		--- */
struct image 	
{	
  short       nlig; 	/* nombre de lignes 2 octets */
  short       ncol; 	/* nombre de colonnes 2 octets */
  unsigned char prof; 	/* profondeur de l'image en octets ou type sinon */
  PDATA       ptdata;   /* donnees : pixels */
};

typedef struct image IMAGE;

/* --- Structure Point --- */
struct point
{
  short   x; /* Coordonnee en x */
  short   y; /* Coordonnee en y */
};

typedef struct point POINT;

/* --- Structure de Boite englobante --- */
struct box
{
  short   box_xmin; /* minimum sur x */
  short   box_xmax; /* maximum sur x */
  short   box_ymin; /* minimum sur y */
  short   box_ymax; /* maximum sur y */
};

typedef struct box BOX;
typedef BOX* PT_BOX;

/* --------------------------------------------------------------*/
/*    MACROS D'ACCES AUX DIVERS DONNEES DES STRUCTURES           */ 
/*    ET DE CREATION DYNAMIQUE DES DONNEES                       */
/* --------------------------------------------------------------*/
/* --- Union de Donnee Image --- */
#define POCTET(XX) ((XX)->poctet) /* l'adresse des donnees de type octet */
#define PETIQ(XX) ((XX)->petiq)/*l'adresse des donnees entier non signe court*/
#define PSUBIM(XX) ((XX)->psubim) /* l'adresse des donnees entier court */
#define PREEL(XX) ((XX)->preel) /* l'adresse des donnees reelles */
		      
/* --- Structure Image --- */
#define NLIG(XX) ((XX)->nlig) /* pour obtenir le nombre de lignes */
#define NCOL(XX) ((XX)->ncol) /* pour obtenir le nombre de colonnes */
#define PROF(XX) ((XX)->prof) /* pour obtenir la profondeur */

/* l'adresse de l'union contenant l'adresse des donnees */
#define PTDATA(XX) ((XX)->ptdata) 

/* creation dynamique de la structure image */

#define crea_IMAGE(XX) ((XX) = (IMAGE *)MALLOC(sizeof(IMAGE)))
#define PIOCTET(XX) ((XX)->ptdata.poctet) /* adresse des octets image */
#define PIETIQ(XX) ((XX)->ptdata.petiq)/*adresse des short unsigned int image*/
#define PISUB(XX) ((XX)->ptdata.psubim) /* adresse des signed short */ 
#define PIFLOAT(XX) ((XX)->ptdata.preel) /* adresse des octets image */

/* --- Structure Point --- */
#define POINT_X(XX) ((XX)->x)
#define POINT_Y(XX) ((XX)->y)

/* pour creer le point */
#define crea_POINT(XX) ((XX) = (POINT *)MALLOC(sizeof(POINT)))
#define init_POINT(XX,YY,ZZ) (POINT_X(XX)=(YY);POINT_Y(XX)=(ZZ)) 			
/* --- Acces aux Donnees Image: N&B, Etiquette, ou Couleur --- */

/* --- Image en Noir et Blanc --- */
#define PIXEL(XX,YY) (*(((XX)->ptdata.poctet)+(long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y))) 

/* --- Image des Etiquettes --- */
#define ETIQ(XX,YY) (*(((XX)->ptdata.petiq)+(long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)))


/* --- Image des Differences --- */
#define SUBPEL(XX,YY) (*(((XX)->ptdata.psubim)+(long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y))) 

/* --- Image en Couleur: R, V, B --- */
/* plan Rouge */
#define PIXEL_R(XX,YY) (*(((XX)->ptdata.poctet)+3*((long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)))) 

/* plan Vert */
#define PIXEL_V(XX,YY) (*(((XX)->ptdata.poctet)+3*((long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)) + 1))

/* plan Bleu */
#define PIXEL_B(XX,YY) (*(((XX)->ptdata.poctet)+3*((long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)) + 2)) 

/* --- Boite englobante --- */
#define crea_BOX(XX) ((XX) = (BOX  *)MALLOC(sizeof(BOX)))
#define BOX_XMIN(XX) ((XX)->box_xmin)
#define BOX_XMAX(XX) ((XX)->box_xmax)
#define BOX_YMIN(XX) ((XX)->box_ymin)
#define BOX_YMAX(XX) ((XX)->box_ymax)

#endif















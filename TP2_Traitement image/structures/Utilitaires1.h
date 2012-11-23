/* -----------------------------------------------------------*/
/*  Prototypes des Fonctions de Lecture, Ecriture,            */
/*  et Creation d'Images                                      */
/*  Environnement Restreint pour TP d'Etudiants               */
/*  sous GCC / Linux                                          */
/*  Fichier: Utilitaires1.h				      */
/*  Auteur: Patrick Bonnin				      */
/*  Date: Modification : Octobre 2000 			      */
/* -----------------------------------------------------------*/

void Creation_Image (IMAGE *image, short *pnlig, short *pncol,
		    unsigned char *pprof);
void Libere_Image(IMAGE *image);
void Lecture_Image(FILE *fichier, IMAGE *image);
void EnregistreImage (FILE *fichier, IMAGE *image);
void Conversion_Image(IMAGE *image, IMAGE *imcoul);
void Inversion(IMAGE *image, IMAGE *imres);
void Lecture_EntetePGM(FILE *fichier, short *pncol, short *pnlig);
void Lecture_EntetePPM(FILE *fichier, short *pncol, short *pnlig);










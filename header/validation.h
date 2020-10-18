#ifndef _VALIDATION_H_
#define _VALIDATION_H_

int validation_fichier(FILE* fic, char* nom);

int validation_mur_haut(unsigned short int** matrice,int nbCol);
int validation_mur_bas(unsigned short int** matrice,int nbLin,int nbCol);
int validation_mur_gauche(unsigned short int** matrice,int nbLin,int nbCol);
int validation_mur_droite(unsigned short int** matrice,int nbLin,int nbCol);

int validation_contour(unsigned short int** matrice,int nbLin,int nbCol);

int validation_interne(unsigned short int** matrice,int nbLin,int nbCol);

int validation_segments_externes(unsigned short int** matrice,int nbLin,int nbCol);

int validation_segment_haut(unsigned short int** matrice,int nbLin,int nbCol);
int validation_segment_droite(unsigned short int** matrice,int nbLin,int nbCol);
int validation_segment_bas(unsigned short int** matrice,int nbLin,int nbCol);
int validation_segment_gauche(unsigned short int** matrice,int nbLin,int nbCol);
#endif
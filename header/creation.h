#ifndef _CREATION_H_
#define _CREATION_H_

FILE* creation_fichier(int nbLin, int nbCol, char* nom);
unsigned short int** init_matrice(int nbLignes, int nbColonnes);
void cassage_interne(unsigned short int** matrice,int nbLin,int nbCol);
void cassage_segments_externes(unsigned short int** matrice,int nbLin,int nbCol);
void cassage_segment_haut(unsigned short int** matrice,int nbLin,int nbCol);
void cassage_segment_droite(unsigned short int** matrice,int nbLin,int nbCol);
void cassage_segment_bas(unsigned short int** matrice,int nbLin,int nbCol);
void cassage_segment_gauche(unsigned short int** matrice,int nbLin,int nbCol);
void rebouche_interne(unsigned short int** matrice,int nbLin,int nbCol);
void rebouche_segments_externes(unsigned short int** matrice,int nbLin,int nbCol);
void rebouche_segment_haut(unsigned short int** matrice,int nbLin,int nbCol);
void rebouche_segment_droite(unsigned short int** matrice,int nbLin,int nbCol);
void rebouche_segment_bas(unsigned short int** matrice,int nbLin,int nbCol);
void rebouche_segment_gauche(unsigned short int** matrice,int nbLin,int nbCol);
#endif
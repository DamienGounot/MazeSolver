#ifndef _INIT_H_
#define _INIT_H_
LABYRINTHE allocation_labyrinthe(int nbLignes, int nbColonnes);
void LIB_MAT(int NB_L,int** MAT);
void init_Labyrinthe(int NB_L, int NB_C, u_int16_t** MAT, FILE* FIC,char* filename);
int validation_fichier(FILE* fic, char* nom);
void affectation_paramettres(int nbLignes,int nbcolones, int Entree_x, int Entree_y, int Sortie_x, int Sortie_y);
#endif
#ifndef _INIT_H_
#define _INIT_H_
LABYRINTHE init_labyrinthe(FILE* FIC,char* filename);
void free_mat(int NB_L,unsigned short int** MAT);
void remplissage_Map(LABYRINTHE labyrinthe,FILE* FIC,char* filename);

#endif
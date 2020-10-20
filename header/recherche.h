#ifndef _RECHERCHE_H_
#define _RECHERCHE_H_

int IA(LABYRINTHE labyrinthe);
int get_mur_value(unsigned short int** map,int IA_x,int IA_y,int direction);
int get_mur_invisible_value(unsigned short int** map,int IA_x,int IA_y,int direction);
int est_franchissable(unsigned short int** map,int IA_x,int IA_y,int direction);
int est_piege(unsigned short int** map,int IA_x,int IA_y);
void poser_mur_invisible(unsigned short int** map,int IA_x,int IA_y,int direction);
void move_IA(LABYRINTHE labyrinthe,int IA_x,int IA_y,int direction);
int get_next_case_mur_invisible_value(unsigned short int** map,int IA_x,int IA_y,int direction);
#endif
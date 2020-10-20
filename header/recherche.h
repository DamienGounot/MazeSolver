#ifndef _RECHERCHE_H_
#define _RECHERCHE_H_

void IA(LABYRINTHE labyrinthe);
int get_mur_value(unsigned short int** map,int IA_x,int IA_y,int direction);
int get_mur_invisible_value(unsigned short int** map,int IA_x,int IA_y,int direction);
int est_piege(unsigned short int** map,int IA_x,int IA_y);
void poser_mur_invisible(unsigned short int** map,int IA_x,int IA_y,int direction);
void move_IA(LABYRINTHE labyrinthe,int IA_x,int IA_y,int direction);
int get_next_case_mur_invisible_value(unsigned short int** map,int IA_x,int IA_y,int direction);
void edit_bit_passage(LABYRINTHE labyrinthe,int IA_x,int IA_y);
int check_cul_de_sac(unsigned short int** map,int IA_x,int IA_y,int direction);
int check_win(int IA_x, int IA_y,int sortie_x, int sortie_y);
#endif
#ifndef _RECHERCHE_H_
#define _RECHERCHE_H_

void IA(LABYRINTHE* labyrinthe);
int get_mur_value(LABYRINTHE* labyrinthe,int direction);
int get_mur_invisible_value(LABYRINTHE* labyrinthe,int direction);
int est_piege(LABYRINTHE* labyrinthe);
void poser_mur_invisible(LABYRINTHE* labyrinthe,int direction);
void move_IA(LABYRINTHE* labyrinthe,int direction);
int get_next_case_mur_invisible_value(LABYRINTHE* labyrinthe,int direction);
int check_cul_de_sac(LABYRINTHE* labyrinthe);
int check_win(LABYRINTHE* labyrinthe);
int check_double_wall(LABYRINTHE* labyrinthe, int direction);
int check_wall(LABYRINTHE* labyrinthe, int direction);
void kill_boucle(LABYRINTHE* labyrinthe,int direction);
#endif
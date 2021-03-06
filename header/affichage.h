#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

void display_menu(char* nom_fichier);
void affiche_u_int16_t(unsigned short int element);
void affichage_labyrinthe(LABYRINTHE labyrinthe);
int get_bit3_value(unsigned short int carre);
int get_bit2_value(unsigned short int carre);
int get_bit1_value(unsigned short int carre);
int get_bit0_value(unsigned short int carre);
int get_case_value(unsigned short int carre);
void debug_mode(char** argv,int argc);
void update_Path(LABYRINTHE* labyrinthe);
void print_Entree__Sortie(LABYRINTHE* labyrinthe);
void reset_cursor(LABYRINTHE* labyrinthe);

#endif
#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct labyrinthe
{
    int nbLignes;
    int nbColonnes;
    unsigned short int** map;
    int entree_x;
    int entree_y;
    int sortie_x;
    int sortie_y;
    int IA_x;
    int IA_y;

}LABYRINTHE;

int debug;


#endif
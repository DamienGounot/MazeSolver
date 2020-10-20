#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/recherche.h"
#include "../header/affichage.h"
#include <time.h>

int IA(LABYRINTHE labyrinthe)
{
    srand(time(NULL));
    int piege = 0;
    int next_direction;
    int mur_value,mur_invisible_value,next_case_mur_invisible_value;
    
    do
    {
        next_direction = rand()%4; // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
        mur_value = get_mur_value(labyrinthe.map,labyrinthe.IA_x,labyrinthe.IA_y,next_direction);
        mur_invisible_value = get_mur_invisible_value(labyrinthe.map,labyrinthe.IA_x,labyrinthe.IA_y,next_direction);

// si cette direction de notre case n'est pas murée ET que l'on est pas déjà passé par là (mur invisible)        
        if (!mur_value && !mur_invisible_value) 
        {
            poser_mur_invisible(labyrinthe.map,labyrinthe.IA_x,labyrinthe.IA_y,next_direction);
        }
        
    }while (1);
    return 1;
}

int get_mur_value(unsigned short int** map,int IA_x,int IA_y,int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{   
    int mur_value = (map[IA_x][IA_y]>>direction)&1;
    if(debug) printf("[DEBUG][get_mur_value] (%d,%d) valeur du mur direction %d: %d\n",IA_x,IA_y,direction,mur_value);
    return mur_value;
}

int get_mur_invisible_value(unsigned short int** map,int IA_x,int IA_y,int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{  
    int mur_invisible = (map[IA_x][IA_y]>>(direction+4))&1;
    if(debug) printf("[DEBUG][get_mur_invisible_value] (%d,%d) valeur du mur invisible direction %d: %d\n",IA_x,IA_y,direction,mur_invisible);
    return mur_invisible;
}
int get_next_case_mur_invisible_value(unsigned short int** map,int IA_x,int IA_y,int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{  
    int mur_invisible;

    switch (direction)
    {
    case 0: //  Gauche
        mur_invisible = (map[IA_x][IA_y-1]>>(direction+4))&1;
        break;
    case 1: //Bas
        mur_invisible = (map[IA_x+1][IA_y]>>(direction+4))&1;
        break;
    case 2: //Droite
        mur_invisible = (map[IA_x][IA_y+1]>>(direction+4))&1;
        break;
    case 3:// Haut
        mur_invisible = (map[IA_x-1][IA_y]>>(direction+4))&1;
        break;                    

    }

    if(debug) printf("[DEBUG][get_next_case_mur_invisible_value] (%d,%d) valeur du mur invisible direction %d: %d\n",IA_x,IA_y,direction,mur_invisible);
    return mur_invisible;
}
int est_franchissable(unsigned short int** map,int IA_x,int IA_y,int direction)
{
    switch (direction)
    {
    case 0: //  Gauche
        
        break;
    case 1: //Bas
        
        break;
    case 2: //Droite
        
        break;
    case 3:// Haut
        
        break;                    

    }
}

int est_piege(unsigned short int** map,int IA_x,int IA_y)
{
    int mur_gauche = get_mur_value(map,IA_x,IA_y,0);
    int mur_bas = get_mur_value(map,IA_x,IA_y,1);
    int mur_droite = get_mur_value(map,IA_x,IA_y,2);
    int mur_haut = get_mur_value(map,IA_x,IA_y,3);
    if(debug) printf("[DEBUG][est_piege] (%d;%d)\n",IA_x,IA_y);
    return mur_gauche && mur_bas && mur_droite && mur_haut;
}

void poser_mur_invisible(unsigned short int** map,int IA_x,int IA_y,int direction)
{  
    map[IA_x][IA_y] = map[IA_x][IA_y]^(2*direction);
    if(debug) printf("[DEBUG][poser_mur_invisible] mur insivible posé en (%d;%d): direction %d\n",IA_x,IA_y,direction);
}

void move_IA(LABYRINTHE labyrinthe,int IA_x,int IA_y,int direction)
{
    switch (direction)
    {
        case 0: //  Gauche
            labyrinthe.IA_y = labyrinthe.IA_y +1;
            break;
        case 1: //Bas
                labyrinthe.IA_x = labyrinthe.IA_x +1;

            break;
        case 2: //Droite
            labyrinthe.IA_y = labyrinthe.IA_y -1;
            break;
        case 3:// Haut
            labyrinthe.IA_x = labyrinthe.IA_x -1;
            break;                    
    }
    if(debug) printf("[DEBUG][move_IA] Ancienne position (%d;%d): direction %d, new position (%d,%d)\n",IA_x,IA_y,direction,labyrinthe.IA_x,labyrinthe.IA_y);

}

#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/recherche.h"
#include "../header/affichage.h"
#include <time.h>

void IA(LABYRINTHE* labyrinthe)
{
    srand(time(NULL));
    int piege = 0;
    int next_direction;
    int mur_value, next_case_mur_invisible_value;//,mur_invisible_value;
    int win = 0;

    piege = est_piege(labyrinthe);

    

    while (!win && !piege)
    {
        win = check_win(labyrinthe);
        next_direction = rand() % 4; // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
        if(debug) printf("Rand next direction: %d\n",next_direction);
        mur_value = get_mur_value(labyrinthe, next_direction);

        if ((!mur_value))
        {
            // si pas de mur sur notre case dans cette direction  (nb: on risque pas de Segfault)
            //mur_invisible_value = get_mur_invisible_value(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
            next_case_mur_invisible_value = get_next_case_mur_invisible_value(labyrinthe, next_direction);

            if ((!next_case_mur_invisible_value))
            {
                // si pas de mur invisible sur la next case (cf on est pas déjà passée dessus)
                poser_mur_invisible(labyrinthe, next_direction);
                // on pose un mur invisible sur notre case
                move_IA(labyrinthe, next_direction);
                // on bouge a l'autre case
            }
            else
            {
                // ici soit cul de sac, soit autre chemin possible
                
                int cul_de_sac = check_cul_de_sac(labyrinthe, next_direction);
                if (cul_de_sac == 3)
                {
                    poser_mur_invisible(labyrinthe, next_direction);
                    move_IA(labyrinthe, next_direction);
                }
                if (cul_de_sac == 4)
                {
                  exit(EXIT_SUCCESS);  
                }
            }
        }
    }

}

int get_mur_value(LABYRINTHE* labyrinthe, int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{
    int mur_value = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] >> direction) & 1;
    if (debug)
        printf("[DEBUG][get_mur_value] (%d,%d) valeur du mur direction %d: %d\n", labyrinthe->IA_x, labyrinthe->IA_y, direction, mur_value);
    return mur_value;
}

int get_mur_invisible_value(LABYRINTHE* labyrinthe, int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{
    int mur_invisible = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] >> (direction + 4)) & 1;
    if (debug)
        printf("[DEBUG][get_mur_invisible_value] (%d,%d) valeur du mur invisible direction %d: %d\n", labyrinthe->IA_x, labyrinthe->IA_y, direction, mur_invisible);
    return mur_invisible;
}
int get_next_case_mur_invisible_value(LABYRINTHE* labyrinthe, int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{
    int mur_invisible;

    switch (direction)
    {
    case 0: //Gauche
        mur_invisible = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y - 1] >> (direction + 4)) & 1;
        break;
    case 1: //Bas
        mur_invisible = (labyrinthe->map[labyrinthe->IA_x + 1][labyrinthe->IA_y] >> (direction + 4)) & 1;
        break;
    case 2: //Droite
        mur_invisible = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y + 1] >> (direction + 4)) & 1;
        break;
    case 3: //Haut
        mur_invisible = (labyrinthe->map[labyrinthe->IA_x - 1][labyrinthe->IA_y] >> (direction + 4)) & 1;
        break;
    }

    if (debug)
        printf("[DEBUG][get_next_case_mur_invisible_value] (%d,%d) valeur du mur invisible voisin direction %d: %d\n", labyrinthe->IA_x, labyrinthe->IA_y, direction, mur_invisible);
    return mur_invisible;
}

int est_piege(LABYRINTHE* labyrinthe)
{
    int mur_gauche = get_mur_value(labyrinthe, 0);
    int mur_bas = get_mur_value(labyrinthe, 1);
    int mur_droite = get_mur_value(labyrinthe, 2);
    int mur_haut = get_mur_value(labyrinthe, 3);
    if (debug)
        printf("[DEBUG][est_piege] check a (%d;%d)\n", labyrinthe->IA_x, labyrinthe->IA_y);
    return mur_gauche && mur_bas && mur_droite && mur_haut;
}

void poser_mur_invisible(LABYRINTHE* labyrinthe, int direction)
{
    switch (direction)
    {
    case 0:
        labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] | 16);
        break;
    case 1:
        labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] | 32);
        break;
    case 2:
        labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] | 64);
        break;
    case 3:
        labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y] | 128);
        break;                    
    default:
        break;
    }
    if (debug)
        printf("[DEBUG][poser_mur_invisible] mur insivible posé en (%d;%d): direction %d\n", labyrinthe->IA_x, labyrinthe->IA_y, direction);
}

void move_IA(LABYRINTHE* labyrinthe, int direction)
{
    int previous_x = labyrinthe->IA_x;
    int previous_y = labyrinthe->IA_y;
    switch (direction)
    {
    case 0: //  Gauche
        labyrinthe->IA_y = labyrinthe->IA_y - 1;
        break;
    case 1: //Bas
        labyrinthe->IA_x = labyrinthe->IA_x + 1;

        break;
    case 2: //Droite
        labyrinthe->IA_y = labyrinthe->IA_y + 1;
        break;
    case 3: // Haut
        labyrinthe->IA_x = labyrinthe->IA_x - 1;
        break;
    }
    if (debug)
        printf("[DEBUG][move_IA] Ancienne position (%d;%d): direction %d, new position (%d,%d)\n", previous_x, previous_y, direction, labyrinthe->IA_x, labyrinthe->IA_y);
}


int check_cul_de_sac(LABYRINTHE* labyrinthe, int direction)
{
    int w_haut = 0, w_bas = 0, w_gauche = 0, w_droite = 0;
    int dw_haut = 0, dw_bas = 0, dw_gauche = 0, dw_droite = 0;

    switch (direction)
    {
    case 0: //  Gauche
       w_bas = check_wall(labyrinthe,1);
       w_haut = check_wall(labyrinthe,3);
       w_droite = check_wall(labyrinthe,2);
        if (!w_bas)
        {
            dw_bas = check_double_wall(labyrinthe,1);
        }
        if (!w_haut)
        {
            dw_haut = check_double_wall(labyrinthe,3);
        }        
        if (!w_droite)
        {
            dw_droite = check_double_wall(labyrinthe,2);
        }
        return (dw_bas + dw_haut + dw_droite) +(w_bas + w_haut + w_droite);    
        break;
    case 1: //Bas
       w_gauche = check_wall(labyrinthe,0);
       w_haut = check_wall(labyrinthe,3);
       w_droite = check_wall(labyrinthe,2);
        if (!w_gauche)
        {
            dw_gauche = check_double_wall(labyrinthe,0);
        }
        if (!w_haut)
        {
            dw_haut = check_double_wall(labyrinthe,3);
        }        
        if (!w_droite)
        {
            dw_droite = check_double_wall(labyrinthe,2);
        }
        return (dw_droite + dw_haut + dw_gauche) +(w_droite + w_haut + w_gauche);
        break;
    case 2: //Droite
       w_gauche = check_wall(labyrinthe,0);
       w_haut = check_wall(labyrinthe,3);
       w_bas = check_wall(labyrinthe,1);
        if (!w_gauche)
        {
            dw_gauche = check_double_wall(labyrinthe,0);
        }
        if (!w_haut)
        {
            dw_haut = check_double_wall(labyrinthe,3);
        }        
        if (!w_bas)
        {
            dw_bas = check_double_wall(labyrinthe,1);
        }
        return (dw_bas + dw_haut + dw_gauche) +(w_bas + w_haut + w_gauche);
        break;
    case 3: // Haut
       w_gauche = check_wall(labyrinthe,0);
       w_droite= check_wall(labyrinthe,2);
       w_bas = check_wall(labyrinthe,1);
        if (!w_gauche)
        {
            dw_gauche = check_double_wall(labyrinthe,0);
        }
        if (!w_droite)
        {
            dw_droite = check_double_wall(labyrinthe,2);
        }        
        if (!w_bas)
        {
            dw_bas = check_double_wall(labyrinthe,1);
        }

        return (dw_bas + dw_droite + dw_gauche) +(w_bas + w_droite + w_gauche);
        break;

        default:
        return EXIT_FAILURE;
        break;
    }
    

}

int check_win(LABYRINTHE* labyrinthe)
{
    if (labyrinthe->IA_x == labyrinthe->sortie_x && labyrinthe->IA_y == labyrinthe->sortie_y)
    {
        if(debug) printf("[DEBUG][check_win] win at (%d,%d)\n", labyrinthe->IA_x, labyrinthe->IA_y);
        return 1;
    }else
    {
        //if(debug) printf("[DEBUG][check_win] not win at (%d,%d)\n", IA_x, IA_y);
        return 0;
    }
    
}
int check_double_wall(LABYRINTHE* labyrinthe, int direction)
{
    int dir;
    int dir_next;

    switch (direction)
    {
    case 0: //  Gauche
        dir = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>(0+4))&1;
        dir_next = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y-1]>>(0+4))&1;              
        break;
    case 1: //Bas
        dir = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>(1+4))&1;
        dir_next = (labyrinthe->map[labyrinthe->IA_x+1][labyrinthe->IA_y]>>(1+4))&1;        
        break;
    case 2: //Droite
        dir = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>(2+4))&1;
        dir_next = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y+1]>>(2+4))&1;                  
        break;
    case 3: // Haut
        dir = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>(3+4))&1;
        dir_next = (labyrinthe->map[labyrinthe->IA_x-1][labyrinthe->IA_y]>>(3+4))&1;                        
        break;
    }

    if (dir == dir_next)
    {
        if (debug) printf("[DEBUG][check_double_wall] Double Wall (%d;%d): direction %d : 1\n", labyrinthe->IA_x, labyrinthe->IA_y, dir);
        return 1;
    }else
    {
        if (debug) printf("[DEBUG][check_double_wall] Double Wall (%d;%d): direction %d : 0\n", labyrinthe->IA_x, labyrinthe->IA_y, dir);
        return 0;
    }
    
    

}

int check_wall(LABYRINTHE* labyrinthe, int direction)
{
    int haut,bas,gauche,droite;

    switch (direction)
    {
    case 0: //  Gauche
        gauche = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>0)&1;
        return gauche;
        break;
    case 1: //Bas
        bas = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>1)&1;
        return bas;
        break;
    case 2: //Droite
        droite = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>2)&1;
        return droite;
        break;
    case 3: // Haut
        haut = (labyrinthe->map[labyrinthe->IA_x][labyrinthe->IA_y]>>3)&1; 
        return haut;   
        break;
        default:
        return EXIT_FAILURE;
        break;
    }   
}
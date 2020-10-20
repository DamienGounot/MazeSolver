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
    int mur_value, mur_invisible_value, next_case_mur_invisible_value;

    piege = est_piege(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y);
    if (piege)
    {
        return 0;
    }

    do
    {
        next_direction = rand() % 4; // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
        mur_value = get_mur_value(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);

        if ((!mur_value))
        {
            // si pas de mur sur notre case dans cette direction  (nb: on risque pas de Segfault)
            mur_invisible_value = get_mur_invisible_value(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
            next_case_mur_invisible_value = get_next_case_mur_invisible_value(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);

            if ((!next_case_mur_invisible_value))
            {
                // si pas de mur invisible sur la next case (cf on est pas déjà passée dessus)
                poser_mur_invisible(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
                // on pose un mur invisible sur notre case
                move_IA(labyrinthe, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
                // on bouge a l'autre case
            }
            else
            {
                int cul_de_sac = check_cul_de_sac(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
                if (cul_de_sac)
                {
                    poser_mur_invisible(labyrinthe.map, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
                    move_IA(labyrinthe, labyrinthe.IA_x, labyrinthe.IA_y, next_direction);
                }
            }
        }
    } while (1);
    return 1;
}

int get_mur_value(unsigned short int **map, int IA_x, int IA_y, int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{
    int mur_value = (map[IA_x][IA_y] >> direction) & 1;
    if (debug)
        printf("[DEBUG][get_mur_value] (%d,%d) valeur du mur direction %d: %d\n", IA_x, IA_y, direction, mur_value);
    return mur_value;
}

int get_mur_invisible_value(unsigned short int **map, int IA_x, int IA_y, int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{
    int mur_invisible = (map[IA_x][IA_y] >> (direction + 4)) & 1;
    if (debug)
        printf("[DEBUG][get_mur_invisible_value] (%d,%d) valeur du mur invisible direction %d: %d\n", IA_x, IA_y, direction, mur_invisible);
    return mur_invisible;
}
int get_next_case_mur_invisible_value(unsigned short int **map, int IA_x, int IA_y, int direction) // 0 pour Gauche, 1 pour Bas, 2 pour Droite, 3 pour Haut
{
    int mur_invisible;

    switch (direction)
    {
    case 0: //Gauche
        mur_invisible = (map[IA_x][IA_y - 1] >> (direction + 4)) & 1;
        break;
    case 1: //Bas
        mur_invisible = (map[IA_x + 1][IA_y] >> (direction + 4)) & 1;
        break;
    case 2: //Droite
        mur_invisible = (map[IA_x][IA_y + 1] >> (direction + 4)) & 1;
        break;
    case 3: //Haut
        mur_invisible = (map[IA_x - 1][IA_y] >> (direction + 4)) & 1;
        break;
    }

    if (debug)
        printf("[DEBUG][get_next_case_mur_invisible_value] (%d,%d) valeur du mur invisible direction %d: %d\n", IA_x, IA_y, direction, mur_invisible);
    return mur_invisible;
}

int est_piege(unsigned short int **map, int IA_x, int IA_y)
{
    int mur_gauche = get_mur_value(map, IA_x, IA_y, 0);
    int mur_bas = get_mur_value(map, IA_x, IA_y, 1);
    int mur_droite = get_mur_value(map, IA_x, IA_y, 2);
    int mur_haut = get_mur_value(map, IA_x, IA_y, 3);
    if (debug)
        printf("[DEBUG][est_piege] check a (%d;%d)\n", IA_x, IA_y);
    return mur_gauche && mur_bas && mur_droite && mur_haut;
}

void poser_mur_invisible(unsigned short int **map, int IA_x, int IA_y, int direction)
{
    map[IA_x][IA_y] = map[IA_x][IA_y] | (2 * direction);
    if (debug)
        printf("[DEBUG][poser_mur_invisible] mur insivible posé en (%d;%d): direction %d\n", IA_x, IA_y, direction);
}

void move_IA(LABYRINTHE labyrinthe, int IA_x, int IA_y, int direction)
{
    switch (direction)
    {
    case 0: //  Gauche
        labyrinthe.IA_y = labyrinthe.IA_y + 1;
        break;
    case 1: //Bas
        labyrinthe.IA_x = labyrinthe.IA_x + 1;

        break;
    case 2: //Droite
        labyrinthe.IA_y = labyrinthe.IA_y - 1;
        break;
    case 3: // Haut
        labyrinthe.IA_x = labyrinthe.IA_x - 1;
        break;
    }
    if (debug)
        printf("[DEBUG][move_IA] Ancienne position (%d;%d): direction %d, new position (%d,%d)\n", IA_x, IA_y, direction, labyrinthe.IA_x, labyrinthe.IA_y);
}

void edit_bit_passage(LABYRINTHE labyrinthe, int IA_x, int IA_y)
{
    labyrinthe.map[IA_x][IA_y] = labyrinthe.map[IA_x][IA_y] ^ 256; //(pour resset au cas ou)
    labyrinthe.map[IA_x][IA_y] = labyrinthe.map[IA_x][IA_y] | 256; // bit de passage a 1
}

int check_cul_de_sac(unsigned short int **map, int IA_x, int IA_y, int direction)
{
    int haut, bas, gauche, droite;

    switch (direction)
    {
    case 0: //  Gauche
        haut = get_mur_value(map, IA_x, IA_y, 3);
        bas = get_mur_value(map, IA_x, IA_y, 1);
        droite = get_mur_value(map, IA_x, IA_y, 2);

        if ((haut + bas + droite) == 3) // si cul de sac
        {
            if (debug)
                printf("[DEBUG][check_cul_de_sac] cul de sac en (%d,%d)\n", IA_x, IA_y);
            return 1;
        }
        else
        {
            return 0;
        }

        break;
    case 1: //Bas

        haut = get_mur_value(map, IA_x, IA_y, 3);
        gauche = get_mur_value(map, IA_x, IA_y, 0);
        droite = get_mur_value(map, IA_x, IA_y, 2);

        if ((haut + gauche + droite) == 3) // si cul de sac
        {
            if (debug)
                printf("[DEBUG][check_cul_de_sac] cul de sac en (%d,%d)\n", IA_x, IA_y);
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 2: //Droite

        haut = get_mur_value(map, IA_x, IA_y, 3);
        bas = get_mur_value(map, IA_x, IA_y, 1);
        gauche = get_mur_value(map, IA_x, IA_y, 0);

        if ((haut + bas + gauche) == 3) // si cul de sac
        {
            if (debug)
                printf("[DEBUG][check_cul_de_sac] cul de sac en (%d,%d)\n", IA_x, IA_y);
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 3: // Haut
        gauche = get_mur_value(map, IA_x, IA_y, 0);
        bas = get_mur_value(map, IA_x, IA_y, 1);
        droite = get_mur_value(map, IA_x, IA_y, 2);

        if ((gauche + bas + droite) == 3) // si cul de sac
        {
            if (debug)
                printf("[DEBUG][check_cul_de_sac] cul de sac en (%d,%d)\n", IA_x, IA_y);
            return 1;
        }
        else
        {
            return 0;
        }
        break;

        default:
        return EXIT_FAILURE;
        break;
    }
    

}

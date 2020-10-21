#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/affichage.h"
#include <string.h>

void display_menu(char *nom_fichier)
{
    FILE *menu = NULL;
    char caract;

    menu = fopen(nom_fichier, "r");
    if (menu == NULL)
    {
       if(debug) printf("[DEBUG][display_menu] Pas de menu ! \n");
        exit(-1);
    }
    system("clear");
    while (caract != EOF)
    {
        caract = fgetc(menu);
        printf("%c", caract);
    }
    fclose(menu);
}

void affiche_u_int16_t(unsigned short int element)
{
    printf("Valeur u_int16_t de %d: ", element);

    for (int k = 15; k >= 0; k--)
    {
        printf("%c", (element >> k) & 1 ? '1' : '0');
    }
    printf("\n");
}

void affichage_labyrinthe(LABYRINTHE labyrinthe)
{
    couleur("31");
    int bit3, bit2, bit1, bit0;

    for (int i = 0; i < labyrinthe.nbLignes; i++)
    {
        for (int k = 0; k < 3; k++) // boucle de 3 pour le print de chaque case
        {
            for (int j = 0; j < labyrinthe.nbColonnes; j++)
            {
                bit3 = get_bit3_value(labyrinthe.map[i][j]);
                bit2 = get_bit2_value(labyrinthe.map[i][j]);
                bit1 = get_bit1_value(labyrinthe.map[i][j]);
                bit0 = get_bit0_value(labyrinthe.map[i][j]);

                switch (k)
                {
                case 0: // print premiere ligne de la case
                    if (bit3)
                    {
                        printf("╬═╬");
                    }
                    else
                    {
                        printf("╬ ╬");
                    }
                    break;
                case 1: // print deuxieme ligne de la case
                    if (bit0 == 0 && bit2 == 0)
                    {
                        printf("   ");
                    }
                    if (bit0 == 0 && bit2 == 1)
                    {
                        printf("  ║");
                    }
                    if (bit0 == 1 && bit2 == 0)
                    {
                        printf("║  ");
                    }
                    if (bit0 == 1 && bit2 == 1)
                    {
                        printf("║ ║");
                    }
                    break;
                case 2: // print troisieme ligne de la case
                    if (bit1)
                    {
                        printf("╬═╬");
                    }
                    else
                    {
                        printf("╬ ╬");
                    }
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
    }
    couleur("0");
}

int get_case_value(unsigned short int carre)
{
    int bit3, bit2, bit1, bit0, result;
    bit3 = (carre >> 3) & 1;
    bit2 = (carre >> 2) & 1;
    bit1 = (carre >> 1) & 1;
    bit0 = (carre >> 0) & 1;
    result = ((bit3 * 8) + (bit2 * 4) + (bit1 * 2) + bit0);
    //if(debug) printf("[DEBUG][get_case_value] valeur des bits de la case: %d\n",result);
    return result;
}

int get_bit3_value(unsigned short int carre)
{
    int bit3;
    bit3 = (carre >> 3) & 1;

    //if(debug) printf("[DEBUG][get_b3_value] valeur de bit3: %d\n",bit3);
    return bit3;
}

int get_bit2_value(unsigned short int carre)
{
    int bit2;
    bit2 = (carre >> 2) & 1;

    //if(debug) printf("[DEBUG][get_b2_value] valeur de bit2: %d\n",bit2);
    return bit2;
}

int get_bit1_value(unsigned short int carre)
{
    int bit1;
    bit1 = (carre >> 1) & 1;
    //if(debug) printf("[DEBUG][get_bit1_value] valeur de bit1: %d\n",bit1);
    return bit1;
}

int get_bit0_value(unsigned short int carre)
{
    int bit0;
    bit0 = (carre >> 0) & 1;
    //if(debug) printf("[DEBUG][get_bit0_value] valeur de bit0: %d\n",bit0);
    return bit0;
}

void debug_mode(char** argv,int argc)
{
    for (int i = 0; i < argc; i++)
    {
        if(!strcmp(argv[i], "debug"))
        {
            debug = 1;
        }
    }
}
void print_Entree__Sortie(LABYRINTHE* labyrinthe)
{
    couleur("36");
    printf("\033[%d;%dH",2+labyrinthe->entree_x*3,2+labyrinthe->entree_y*3);
    printf("S");
    printf("\033[%d;%dH",2+labyrinthe->sortie_x*3,2+labyrinthe->sortie_y*3);
    printf("E");
    couleur("0");
}
void update_Path(LABYRINTHE* labyrinthe)
{
    couleur("33");
    printf("\033[%d;%dH",2+labyrinthe->IA_x*3,2+labyrinthe->IA_y*3);
    printf("*");
    couleur("0");
}

void reset_cursor(LABYRINTHE* labyrinthe)
{
    printf("\033[%d;%dH",4+labyrinthe->nbLignes*3,0);
}


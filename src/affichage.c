#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/affichage.h"

void display_menu(char* nom_fichier)
{
    FILE* menu = NULL;
	char caract;

	menu = fopen(nom_fichier, "r");
        if (menu == NULL)
        {
            printf("[DEBUG][display_menu] Pas de menu ! \n");
        exit(-1);
        }
        system("clear");
        while (caract != EOF)
        {
            caract = fgetc(menu);
            printf("%c",caract);
        }
	fclose(menu);
}

void affiche_u_int16_t(unsigned short int element)
{
    printf("Valeur u_int16_t de %d: ",element);

    for (int k = 15; k >= 0; k--) 
    {
        printf("%c",(element>>k)&1?'1':'0');
    }
    printf("\n");
}

void affichage_labyrinthe(LABYRINTHE labyrinthe)
{
    int valeur;

    for (int i = 0; i < labyrinthe.nbLignes; i++)
    {
        for (int j = 0; j < labyrinthe.nbColonnes; j++)
        {
            valeur = get_case_value(labyrinthe.map[i][j]);

            switch (valeur)
            {
            case 0:
                   
                break;
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                
                break;
            case 8:
                
                break;
            case 9:
                
                break;
            case 10:
                
                break;
            case 11:
                
                break; 
            case 12:
                
                break; 
            case 13:
                
                break; 
            case 14:
                
                break; 
            case 15:
                
                break;                                                                                                                                                                                                                                             
            default:
                break;
            }
        }
        printf("\n");        
    }
}

int get_case_value(unsigned short int carre)
{
    int bit3,bit2,bit1,bit0,result;
    bit3 = (carre>>3)&1;
    bit2 = (carre>>2)&1;
    bit1 = (carre>>1)&1;
    bit0 = (carre>>0)&1;
    result = ((bit3*8) + (bit2*4) + (bit1*2) + bit0);
    //printf("[DEBUG][get_case_value] valeur des bits de la case: %d\n",result);
    return result;
}
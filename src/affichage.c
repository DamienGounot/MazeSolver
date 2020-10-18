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

void affiche_labyrinthe(int NB_L, int NB_C, u_int16_t** MAT)
{
    for (int i = 0; i < NB_L; i++)
    {
        for (int j = 0; j < NB_C; j++)
        {
            //printf("%d",(*(*(MAT+i))+j));
            printf("%2d ",MAT[i][j]);       
        }
        printf("\n");
        
    }
    
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
#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/init.h"

LABYRINTHE allocation_labyrinthe(int nbLignes, int nbColonnes)
{
    LABYRINTHE labyrinthe;
    labyrinthe.map = malloc(sizeof(unsigned short int*)*nbLignes);
    
    for (int i = 0; i < nbLignes; i++)
    {
        labyrinthe.map[i] = malloc(sizeof(unsigned short int)*nbColonnes);
    }
    
    return labyrinthe;
}


void LIB_MAT(int NB_L,int** MAT)
{
    for (int i = 0; i < NB_L; i++)
    {
        free(MAT[i]);
    }
    free(MAT);
}

int validation_fichier(FILE* fic, char* nom)
{
    fic = fopen(nom,"r");
    if (fic == NULL)
    {
        printf("Erreur lors de l'ouverture ");
        return(0);
    }

    char c;
    //.......

}

void init_Labyrinthe(int NB_L, int NB_C, u_int16_t** MAT, FILE* FIC,char* filename)
{
    int valeur;
    char c;

    FIC = fopen(filename,"r");

    if (FIC == NULL)
    {
        printf("Erreur ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }

        fseek(FIC,0,SEEK_SET);

        while (c!='\n') // pour passer la première ligne
        {
            c=getc(FIC);
        }

            for (int i = 0; i < NB_L; i++)
            {
                for (int j = 0; j < NB_C; j++)
                {
                    fscanf(FIC, "%d",&valeur);
                    MAT[i][j] = valeur;
                }
            }
        fclose(FIC);
}

void affectation_paramettres(int nbLignes,int nbcolones, int Entree_x, int Entree_y, int Sortie_x, int Sortie_y)
{

}
#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/init.h"

LABYRINTHE init_labyrinthe(FILE* FIC,char* filename)
{
    int nbLignes,nbColonnes,entreeX,entreeY,sortieX,sortieY;
    FIC = fopen(filename,"r");

    if (FIC == NULL)
    {
        printf("[DEBUG][init_labyrinthe]Erreur lors de l'ouverture\n");
        exit(EXIT_FAILURE);
    }

    fseek(FIC,0,SEEK_SET);
    fscanf(FIC,"%d %d %d %d %d %d",&nbLignes,&nbColonnes,&entreeX,&entreeY,&sortieX,&sortieY);
    fclose(FIC);
    LABYRINTHE labyrinthe;
    labyrinthe.map = malloc(sizeof(unsigned short int*)*nbLignes);
    labyrinthe.nbLignes = nbLignes;
    labyrinthe.nbColonnes = nbColonnes;
    labyrinthe.entree_x = entreeX;
    labyrinthe.entree_y = entreeY;
    labyrinthe.sortie_x = sortieX;
    labyrinthe.sortie_y = sortieY;
    labyrinthe.IA_x = labyrinthe.entree_x;
    labyrinthe.IA_y = labyrinthe.entree_y;
    
    for (int i = 0; i < nbLignes; i++)
    {
        labyrinthe.map[i] = malloc(sizeof(unsigned short int)*nbColonnes);
    }
    
    return labyrinthe;
}


void LIB_MAT(int NB_L,unsigned short int** MAT)
{
    for (int i = 0; i < NB_L; i++)
    {
        free(MAT[i]);
    }
    free(MAT);
}


void remplissage_Map( LABYRINTHE labyrinthe, FILE* FIC,char* filename)
{
    u_int16_t valeur;
    char c;

    FIC = fopen(filename,"r");

    if (FIC == NULL)
    {
        printf("[DEBUG][remplissage_Map]Erreur ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }

        fseek(FIC,0,SEEK_SET);
        while (c !='\n')    //skip la premiere ligne car ne nous interesse pas ici
        {
            c = fgetc(FIC);
        }
            for (int i = 0; i < labyrinthe.nbLignes; i++)
            {
                for (int j = 0; j < labyrinthe.nbColonnes; j++)
                {
                    fscanf(FIC, "%hu",&valeur);
                    labyrinthe.map[i][j] = valeur;
                }
            }
        fclose(FIC);
}
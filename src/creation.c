#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/validation.h"
#include "../header/init.h"
#include <time.h>

FILE *creation_fichier(int nbLin, int nbCol, char *nom)
{
    srand(time(NULL));
    FILE *fic = NULL;
    int validationFichier;
    int valeur;
    unsigned short int matrice = init_matrice(nbLin, nbCol);
    cassage_segments_externes(matrice,nbLin,nbCol);
    cassage_interne(matrice,nbLin,nbCol);

    fic = fopen(nom,"w+");
    if (fic == NULL)
    {
        printf("[DEBUG][creation_fichier] Erreur ecriture dans fichier ! \n");
        exit(EXIT_FAILURE);
    }

        int EntreeX = rand()%nbCol;
        int EntreeY = rand()%nbLin;
        int SortieX = rand()%nbCol;
        int SortieY = rand()%nbLin;

        fprintf(fic,"%d %d %d %d %d %d\n",nbLin,nbCol,EntreeX,EntreeY,SortieX,SortieY);

            for (int i = 0; i < nbLin; i++)
            {
                for (int j = 0; j < nbCol; j++)
                {
                    valeur = matrice[i][j];
                    fprintf(fic,"%d ",valeur);
                }
                fprintf(fic,"\n");
            }
        fclose(fic);
    LIB_MAT(nbLin, matrice);

    return fic;
}

unsigned short int **init_matrice(int nbLignes, int nbColonnes)
{
    unsigned short int **matrice = malloc(sizeof(unsigned short int *) * nbLignes); // allocation matrice, pour pouvoir travailler dessus
    for (int i = 0; i < nbLignes; i++)
    {
        matrice[i] = malloc(sizeof(unsigned short int) * nbColonnes);
    }

        for (int i = 0; i < nbLignes; i++)
        {
            for (int j = 0; j < nbColonnes; j++)
            {
                matrice[i][j] = 15; // initialisation avec 15

            }
        }

    return matrice;
}

void cassage_segment_haut(unsigned short int** matrice,int nbLin,int nbCol)
{
    int random_d,random_b;

    for (int i = 0; i < nbCol-1; i++) // pour tout le segment du haut (sauf derniere case)
    {
        random_d = rand()%4;
        random_b = rand()%4;

        if (!random_d) // proba de 75% de casser le mur 
        {
            matrice[0][i] = (matrice[0][i])^4; // mur droite case en cours
            matrice[0][i+1] = (matrice[0][i+1])^1; // mur gauche case de droite
        }
        
        if (!random_b)// proba de 75% de casser le mur 
        {
            matrice[0][i] = (matrice[0][i])^2; // mur bas case en cours
            matrice[1][i] = (matrice[1][i])^8; // mur haut case du bas
        } 
    }
}

void cassage_segment_droite(unsigned short int** matrice,int nbLin,int nbCol)
{

}

void cassage_segment_bas(unsigned short int** matrice,int nbLin,int nbCol)
{

}

void cassage_segment_gauche(unsigned short int** matrice,int nbLin,int nbCol)
{

}

void cassage_segments_externes(unsigned short int** matrice,int nbLin,int nbCol)
{
    cassage_segment_haut(matrice,nbLin,nbCol);
    cassage_segment_droite(matrice,nbLin,nbCol);
    cassage_segment_bas(matrice,nbLin,nbCol);
    cassage_segment_gauche(matrice,nbLin,nbCol);
}

void cassage_interne(unsigned short int** matrice,int nbLin,int nbCol)
{

}
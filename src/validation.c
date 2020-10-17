#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/validation.h"


int validation_fichier(FILE* fic, char* nom)
{
    int nbLignes,nbColonnes,entreeX,entreeY,sortieX,sortieY;
    unsigned short int element;

    fic = fopen(nom,"r");
    if (fic == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier passé en parametre \n");
        return 0;
    }

    fseek(fic,0,SEEK_SET);
    fscanf(fic,"%d %d %d %d %d %d",&nbLignes,&nbColonnes,&entreeX,&entreeY,&sortieX,&sortieY);


    unsigned short int** matrice = malloc(sizeof(unsigned short int*)*nbLignes); // allocation matrice, pour pouvoir travailler dessus
    for (int i = 0; i < nbLignes; i++)
    {
        matrice[i] = malloc(sizeof(unsigned short int)*nbColonnes);
    }

    for (int i = 0; i < nbLignes; i++) // remplissage matrice, pour pouvoir travailler dessus
    {
        for (int j = 0; j < nbColonnes; j++)
        {
            fscanf(fic,"%hu",&element);
            matrice[i][j] = element;
            printf("Valeur u_int16_t de %d: ",element);
                for (int k = 15; k >= 0; k--) 
                {
                   printf("%c",(element>>k)&1?'1':'0');
                }
                printf("\n");
        }
        
    }

    int valid_contour = validation_contour(matrice,nbLignes,nbColonnes);
    if (!valid_contour)
    {
        printf("[Debug][validation_fichier] contour non valide\n");
        return 0;
    }
    
    // free la matrice
    return 1;
}

int validation_contour(unsigned short int** matrice,int nbLin,int nbCol)
{
   int valid_bas = validation_mur_bas(matrice,nbLin,nbCol);
   int valid_haut = validation_mur_haut(matrice,nbCol);
   int valid_gauche = validation_mur_gauche(matrice,nbLin,nbCol);
   int valid_droite = validation_mur_droite(matrice,nbLin,nbCol);

   return ((valid_haut && valid_bas)&&(valid_droite && valid_gauche));
}

int validation_mur_haut(unsigned short int** matrice,int nbCol)
{
    int bit3;

    for (int i = 0; i < nbCol; i++)
    {
        bit3 = (matrice[0][i]>>3)&1; // decallage 3 bits pour avoir b3

        if (!bit3)
        {
            printf("[Debug][validation_mur_haut] La case 0:%d possède b3 a 0\n",i);
            return 0;
        }                  
    }
    printf("[Debug][validation_mur_haut] Mur haut valide\n");
    return 1;
}

int validation_mur_bas(unsigned short int** matrice,int nbLin,int nbCol)
{
    int bit1;

    for (int i = 0; i < nbCol; i++)
    {
        bit1 = (matrice[nbLin-1][i]>>1)&1; // decallage 1 bits pour avoir b1

        if (!bit1)
        {
            printf("[Debug][validation_mur_bas] La case %d:%d possède b1 a 0\n",nbLin-1,i);
            return 0;
        }                  
    }
    printf("[Debug][validation_mur_bas] Mur bas valide\n");
    return 1;
}

int validation_mur_gauche(unsigned short int** matrice,int nbLin,int nbCol)
{
    int bit0;

    for (int i = 0; i < nbLin; i++)
    {
        bit0 = (matrice[i][0]>>0)&1; // decallage 0 bits pour avoir b0

        if (!bit0)
        {
            printf("[Debug][validation_mur_gauche] La case %d:0 possède b0 a 0\n",i);
            return 0;
        }                  
    }
    printf("[Debug][validation_mur_gauche] Mur gauche valide\n");
    return 1;
}

int validation_mur_droite(unsigned short int** matrice,int nbLin,int nbCol)
{
    int bit2;

    for (int i = 0; i < nbLin; i++)
    {
        bit2 = (matrice[i][nbCol-1]>>2)&1; // decallage 2 bits pour avoir b2

        if (!bit2)
        {
            printf("[Debug][validation_mur_droite] La case %d:%d possède b0 a 0\n",i,nbCol-1);
            return 0;
        }                  
    }
    printf("[Debug][validation_mur_droite] Mur droite valide\n");
    return 1;
}
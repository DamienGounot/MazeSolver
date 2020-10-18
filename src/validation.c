#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
#include "../header/validation.h"
#include "../header/init.h"
#include "../header/affichage.h"


int validation_fichier(FILE* fic, char* nom)
{
    int nbLignes,nbColonnes,entreeX,entreeY,sortieX,sortieY;
    unsigned short int element;

    fic = fopen(nom,"r");
    if (fic == NULL)
    {
        printf("[DEBUG][validation_fichier]Erreur lors de l'ouverture du fichier passé en parametre \n");
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
        }    
    }
    fclose(fic);
    int valid_contour = validation_contour(matrice,nbLignes,nbColonnes);
    int valid_segment = validation_segments_externes(matrice,nbLignes,nbColonnes);
    int valid_interne = validation_interne(matrice,nbLignes,nbColonnes);

    LIB_MAT(nbLignes,matrice);
    return valid_segment && valid_contour && valid_interne;
}

int validation_interne(unsigned short int** matrice,int nbLin,int nbCol)
{
    int case_h,case_b,case_d,case_g;
    int case_haut_b,case_droite_g,case_bas_h,case_gauche_d;

    for (int i = 1; i < nbLin-1; i++)
    {
        for (int j = 1; j < nbCol-1; j++)
        {
            case_h = (matrice[i][j]>>3)&1; //mur haut case actuelle
            case_b = (matrice[i][j]>>1)&1; //mur bas case actuelle
            case_d = (matrice[i][j]>>2)&1; //mur droit case actuelle
            case_g = (matrice[i][j]>>0)&1; //mur gauche case actuelle

            case_haut_b = (matrice[i-1][j]>>1)&1; //mur bas case du haut
            case_droite_g = (matrice[i][j+1]>>0)&1; //mur gauche case de droite
            case_bas_h = (matrice[i+1][j]>>3)&1; //mur haut case du bas
            case_gauche_d = (matrice[i][j-1]>>2)&1; //mur droit case de gauche
            
            if ((case_h != case_haut_b) || (case_b != case_bas_h) || (case_d != case_droite_g) || (case_g != case_gauche_d))
            {
                printf("[Debug][validation_interne] interne non validé, case (%d:%d)\n",i,j);
                return 0;
            }
   
        }   
    }
        printf("[Debug][validation_interne] cases internes validées\n");
        return 1;  
}

int validation_segments_externes(unsigned short int** matrice,int nbLin,int nbCol)
{
    int haut = validation_segment_haut(matrice,nbLin,nbCol);
    int bas = validation_segment_bas(matrice,nbLin,nbCol);
    int gauche = validation_segment_gauche(matrice,nbLin,nbCol);
    int droite = validation_segment_droite(matrice,nbLin,nbCol);

    return((haut && droite)&&(bas && gauche));
}

int validation_segment_haut(unsigned short int** matrice,int nbLin,int nbCol)
{   
    int case_d,case_b,case_bas_h,case_droite_g;

    for (int i = 0; i < nbCol-1; i++) // pour tout le segment du haut (sauf derniere case)
    {
         case_d = (matrice[0][i]>>2)&1; // mur droite case en cours
         case_b = (matrice[0][i]>>1)&1; // mur bas case en cours
         case_bas_h = (matrice[1][i]>>3)&1; // mur haut case du bas
         case_droite_g = (matrice[0][i+1]>>0)&1; // mur gauche case de droite

        if ((case_d != case_droite_g)||(case_b != case_bas_h))
        {
            printf("[Debug][validation_segment_haut] segment haut non valide, case (0:%d)\n",i);
            return 0;
        }   
    }
    printf("[Debug][validation_segment_haut] segment haut valide\n");
    return 1;
}
int validation_segment_droite(unsigned short int** matrice,int nbLin,int nbCol)
{
        int case_g,case_b,case_gauche_d,case_bas_h;
    
    for (int i = 0; i < nbLin-1; i++) // pour tout le segment de droite (sauf derniere case)
    {
         case_g = (matrice[i][nbCol-1]>>0)&1; // mur gauche case en cours
         case_b = (matrice[i][nbCol-1]>>1)&1; // mur bas case en cours
         case_gauche_d = (matrice[i][nbCol-2]>>2)&1; // mur droit case de gauche
         case_bas_h = (matrice[i+1][nbCol-1]>>3)&1; // mur haut case du bas

        if ((case_g != case_gauche_d)||(case_b != case_bas_h))
        {
            printf("[Debug][validation_segment_droite] segment droite non valide, case (%d:%d)\n",i,nbCol-1);
            return 0;
        }   
    }
    printf("[Debug][validation_segment_droite] segment droite valide\n");
    return 1;
}
int validation_segment_bas(unsigned short int** matrice,int nbLin,int nbCol)
{
    int case_g,case_h,case_gauche_d,case_haut_b;

    for (int i = nbCol -1; i > 0; i--) // pour tout le segment du bas (sauf derniere case)
    {
         case_g = (matrice[nbLin-1][i]>>0)&1; // mur gauche case en cours
         case_h = (matrice[nbLin-1][i]>>3)&1; // mur haut case en cours
         case_gauche_d = (matrice[nbLin-1][i-1]>>2)&1; // mur droit case de gauche
         case_haut_b = (matrice[nbLin-2][i]>>1)&1; // mur bas case du haut
        
        if ((case_g != case_gauche_d)||(case_h != case_haut_b))
        {
            printf("[Debug][validation_segment_bas] segment bas non valide, case (%d:%d)\n",nbLin-1,i);
            return 0;
        }   
    }
    printf("[Debug][validation_segment_bas] segment bas valide\n");
    return 1;    
}
int validation_segment_gauche(unsigned short int** matrice,int nbLin,int nbCol)
{
    int case_d,case_h,case_droite_g,case_haut_b;

    for (int i = nbLin -1; i > 0; i--) // pour tout le segment de gauche (sauf derniere case)
    {
         case_d = (matrice[i][0]>>2)&1; // mur droit case en cours
         case_h = (matrice[i][0]>>3)&1; // mur haut case en cours
         case_droite_g = (matrice[i][1]>>0)&1; // mur gauche case de droite
         case_haut_b = (matrice[i-1][0]>>1)&1; // mur bas case du haut
        if ((case_d != case_droite_g)||(case_h != case_haut_b))
        {
            printf("[Debug][validation_segment_gauche] segment gauche non valide, case (%d:%d)\n",i,0);
            return 0;
        }   
    }
    printf("[Debug][validation_segment_gauche] segment gauche valide\n");
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
            printf("[Debug][validation_mur_haut] La case (0:%d) possède b3 a 0\n",i);
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
            printf("[Debug][validation_mur_bas] La case (%d:%d) possède b1 a 0\n",nbLin-1,i);
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
            printf("[Debug][validation_mur_gauche] La case (%d:0) possède b0 a 0\n",i);
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
            printf("[Debug][validation_mur_droite] La case (%d:%d) possède b2 a 0\n",i,nbCol-1);
            return 0;
        }                  
    }
    printf("[Debug][validation_mur_droite] Mur droite valide\n");
    return 1;
}
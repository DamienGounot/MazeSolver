#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/main.h"
#include "../header/init.h"
#include "../header/affichage.h"

int main(int argc, char** argv){
srand(time(NULL));
const int nbLignes;
const int nbColonnes;
char choixMenu;
char* filename;
int validationFichier;
FILE* fichier = NULL;

if (argc>1) // si on passe en paramettre un fichier 
{
    filename = argv[1];
    validationFichier = validation_fichier(fichier,filename); // on le test
}else
{       
        do
        {
        scanf("%c",&choixMenu);
        system("clear");
        display_menu("./UI/menu");
        printf("\033[%d;%dH",14,40);
        
        } while (choixMenu !='1' || choixMenu !='2' );

        if (!choixMenu)
        {
            return(EXIT_SUCCESS);
        }
        // ici creation fichier valide par le programme (A FAIRE)
}
    if (!validationFichier)
    {
        return(EXIT_FAILURE);
    }
    else
    {
        void affectation_paramettres(nbLignes,nbColonnes,Entree_x,Entree_y,Sortie_x,Sortie_y);
    }
    
    

// Ici Environnement avec Carte validée

LABYRINTHE labyrinthe = allocation_labyrinthe(nbLignes,nbColonnes);  // allocation et init de la map
init_Labyrinthe(nbLignes,nbColonnes,labyrinthe.map,fichier,filename);

 
    return EXIT_SUCCESS;
}
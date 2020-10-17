#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/main.h"
#include "../header/init.h"
#include "../header/affichage.h"
#include "../header/validation.h"

int main(int argc, char** argv){
srand(time(NULL));

int choixMenu;
char* filename;
int validationFichier;
FILE* fichier = NULL;

if (argv[1]) // si on passe en paramettre un fichier 
{
    filename = argv[1];
    validationFichier = validation_fichier(fichier,filename); // on le test
    printf("%d",validationFichier);
}else
{       
        while (choixMenu !=1 || choixMenu !=2 )
        {
        system("clear");
        display_menu("./UI/menu");
        printf("\033[%d;%dH",14,40);
        scanf("%d",&choixMenu);
        }

        if (choixMenu == 2)
        {
            return(EXIT_SUCCESS);
        }
        // ici creation fichier valide par le programme (A FAIRE)
}
    if (!validationFichier)
    {
        return(EXIT_FAILURE);
    }

    
    

// Ici Environnement avec Carte validée

LABYRINTHE labyrinthe = init_labyrinthe(fichier,filename);  // allocation et init du labyrinthe
remplissage_Map(labyrinthe,fichier,filename);

 
    return EXIT_SUCCESS;
}
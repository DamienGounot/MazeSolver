#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/main.h"
#include "../header/init.h"
#include "../header/affichage.h"
#include "../header/validation.h"
#include "../header/creation.h"
#include "../header/recherche.h"

int main(int argc, char** argv){
srand(time(NULL));

int choice = 0;
int nbLin = 0;
int nbCol = 0;
char* filename;
int validationFichier;
FILE* fichier = NULL;
    debug_mode(argv,argc);

if (argv[1]) // si on passe en paramettre un fichier 
{ 
    filename = argv[1];
    validationFichier = validation_fichier(fichier,filename); // on le test
}else
{       

        
        display_menu("./UI/menu");
        printf("\033[%d;%dH",14,40);
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
                    display_menu("./UI/init");
                    printf("\033[%d;%dH",14,40);
                        int saisie = scanf("%d %d",&nbLin,&nbCol);
                        // / saisie des dimensions voulues
                        switch (saisie)
                        {
                        case 2:
                            if (nbLin < 3 || nbCol < 3) // si taille saisie insuffisante
                            {
                                printf("\033[%d;%dH",16,0);
                                return(EXIT_SUCCESS);
                            }
                            filename = "./map/random";
                            // creation du fichier par le programme
                            fichier = creation_fichier(nbLin,nbCol,filename);
                            validationFichier = validation_fichier(fichier,filename);
                            break;
                        
                        default:
                            printf("\033[%d;%dH",16,0);
                            return(EXIT_SUCCESS);
                        break;
                        }

			break;
			default:
                    printf("\033[%d;%dH",16,0);
                    return(EXIT_SUCCESS);
			break;
		}
}
    if (!validationFichier)
    {
        printf("[DEBUG][main]Fichier non valide ! \n");
        return(EXIT_FAILURE);
    }

// Ici Environnement avec Carte validée
system("clear");
LABYRINTHE labyrinthe = init_labyrinthe(fichier,filename);  // allocation et init du labyrinthe
remplissage_Map(labyrinthe,fichier,filename);
affichage_labyrinthe(labyrinthe);


    return EXIT_SUCCESS;
}
all : CLEAR COMP CLEAR

CLEAR:
	clear
				
main.o : 
	gcc -c ./src/main.c -o ./obj/main.o -Wall

init.o : 
	gcc -c ./src/init.c  -o ./obj/init.o -Wall

affichage.o : 
	gcc -c ./src/affichage.c -o ./obj/affichage.o -Wall

creation.o : 
	gcc -c ./src/creation.c -o ./obj/creation.o -Wall

validation.o : 
	gcc -c ./src/validation.c  -o ./obj/validation.o -Wall

recherche.o : 
	gcc -c ./src/recherche.c  -o ./obj/recherche.o -Wall

COMP : main.o init.o affichage.o validation.o creation.o recherche.o
	gcc -o COMP ./obj/main.o ./obj/init.o ./obj/affichage.o ./obj/validation.o ./obj/creation.o ./obj/recherche.o -Wall

NETTOYAGE : 
	rm ./obj/*.o

LAUNCH :
	-./COMP map.txt
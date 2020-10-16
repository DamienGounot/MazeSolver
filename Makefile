all : CLEAR COMP CLEAR LAUNCH

CLEAR:
	clear
				
main.o : 
	gcc -c ./src/main.c -o ./obj/main.o -Wall

init.o : 
	gcc -c ./src/init.c  -o ./obj/init.o -Wall

affichage.o : 
	gcc -c ./src/affichage.c -o ./obj/affichage.o -Wall

COMP : main.o init.o affichage.o -Wall
	gcc -o COMP ./obj/main.o ./obj/init.o ./obj/affichage.o -Wall

NETTOYAGE : 
	rm ./obj/*.o

LAUNCH :
	-./COMP -Wall
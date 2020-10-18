all : CLEAR COMP

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

COMP : main.o init.o affichage.o validation.o creation.o
	gcc -o COMP ./obj/main.o ./obj/init.o ./obj/affichage.o ./obj/validation.o ./obj/creation.o -Wall

NETTOYAGE : 
	rm ./obj/*.o

LAUNCH :
	-./COMP map.txt
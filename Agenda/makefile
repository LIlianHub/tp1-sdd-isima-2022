Programme:objet/main.o objet/tete.o objet/semaine.o objet/action.o objet/commun.o objet/contigue.o
	gcc -o Programme objet/main.o objet/tete.o objet/semaine.o objet/action.o objet/commun.o objet/contigue.o -g

objet/main.o:source/main.c headers/commun.h headers/contigue.h
	gcc -c source/main.c -Wall -Wextra -o objet/main.o -g

objet/tete.o:source/tete.c headers/tete.h
	gcc -c source/tete.c -Wall -Wextra -o objet/tete.o -g

objet/semaine.o:source/semaine.c headers/semaine.h
	gcc -c source/semaine.c -Wall -Wextra -o objet/semaine.o -g

objet/action.o:source/action.c headers/action.h
	gcc -c source/action.c -Wall -Wextra -o objet/action.o -g

objet/commun.o:source/commun.c headers/tete.h
	gcc -c source/commun.c -Wall -Wextra -o objet/commun.o -g

objet/contigue.o:source/contigue.c headers/contigue.h headers/commun.h
	gcc -c source/contigue.c -Wall -Wextra -o objet/contigue.o -g





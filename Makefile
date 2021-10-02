all :
	ls niveaux/ > niveaux/liste
	gcc -Wall -o sokoban main.c fonctions.c
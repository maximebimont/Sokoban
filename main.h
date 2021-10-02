//librairies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structures
typedef struct {
    int colonne;
    int ligne;
    char c_temp;
} point_t;

typedef struct {
    char* terrain;
    int nb_colonnes;
    int nb_lignes;
    point_t* perso;
} niveau_t;


typedef struct {
    niveau_t** tableau;
    int taille;
    int idx;
} historique_t;

//autres
#include "fonctions.h"
#include "main.h"

int score = 0;

//exo1
niveau_t* nouveau_niveau(int nb_col, int nb_lig){
	niveau_t* niveau = malloc(sizeof(niveau_t));
	niveau->terrain = malloc(sizeof(char)*(nb_col*nb_lig+nb_col));
	niveau->nb_colonnes = nb_col;
	niveau->nb_lignes = nb_lig;
	return niveau;
}

void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
	niveau->terrain[niveau->nb_colonnes*ligne+colonne]=car;
}

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne){
	return niveau->terrain[niveau->nb_colonnes*ligne+colonne];
}

void initialise_le_terrain (niveau_t* niveau){
	for (int i = 0; i < niveau->nb_lignes; i++){
		for (int j = 0; j < niveau->nb_colonnes; j++){
			place_sur_terrain(niveau,j,i,'&');
		}
	}
}

void affichage_niveau (niveau_t* niveau){
	system("clear");
    for (int i = 0; i < niveau->nb_lignes; i++){
		for (int j = 0; j < niveau->nb_colonnes; j++){
			printf("%c",lecture_du_terrain(niveau,j,i));
		}
		printf("\n");
	}
}

void liberation_du_niveau (niveau_t* niveau){
    free(niveau);
}

niveau_t* lecture_du_niveau(int quel_niveau){
    int colonne;
    int ligne;
    FILE * fichier;
    char niveau[50];//initialise le chemin

    sprintf(niveau,"./niveaux/niveau_%d",quel_niveau);//construit le chemin a partir de l'arg
    fichier = fopen(niveau,"r");//"read" le fichier 

    fscanf(fichier,"%d %d",&colonne,&ligne);
    printf("%i %i",colonne,ligne);
    getc(fichier);//lit le \n
    niveau_t* new_niveau = nouveau_niveau(colonne,ligne);

    int i;
    int j;
    char c;
    for (i = 0; i <= ligne; i++){
    j=-1;
        while(j<=colonne+1){
            if(c!='\n'){
                j++;
                place_sur_terrain(new_niveau,j,i,c);
            }
            while(c=='\n' && j<=colonne+1){
                j++;
                place_sur_terrain(new_niveau,j,i,' ');
            }
            c=getc(fichier);
            if(c=='@'){
                new_niveau->perso = newPerso(j+1,i);
            }
        }
    }
    printf("\n");printf("\n");
    fclose(fichier);
    return new_niveau;
}

//exo2
void suivant(void){
    printf("[ENTRER]");
    char entree;
    entree='&';
    while(entree=='&') scanf("%c", &entree);
}

char menuJeu (void){
    char menu;
    menu = ' ';
    printf("Que voulez-vous faire ?\n\n1. Jouer\n2. Règles\n3. Quitter\n");  
    while( menu != '1' && menu != '2' && menu != '3') scanf("%c", &menu);
    return menu;
}

void regles(void){
    system("clear");
    printf("Règles du jeu :\nVous [@] devez déplacer les caisses [$] vers les zones de chargement [.]\navec le minimum de déplacements possibles. Prenez garde à ne pas les bloquer\ncontre les murs [#]\n");
    char entree;
    entree='&';
    while(entree=='&') scanf("%c", &entree);
}

void bestScore(void){
    system("clear");
    printf("Meilleurs Scores\n\n");
    char entree;
    entree='&';
    while(entree=='&') scanf("%c", &entree);
}

char choixNiveau(void){
    system("clear");
    printf("Choisis ton niveau :\n");
    printf("Voici les niveaux auquel tu as accès : ");
    fflush(stdout);
    system("cat niveaux/liste | tr -d [:alpha:],_~ | sort | uniq | tr -s '\n' ' '");
    printf("\n");
    char entree;
    entree= ' ';
    while(entree!='0' && entree!='1') scanf("%c", &entree);
    return entree;
}

char entree_du_joueur (void){
    char entree;
    entree = ' ';
    printf("\n");
    printf("Où voulez vous aller ? ");  
    while( entree != 'z' && entree != 'q' && entree != 's' && entree != 'd' && entree != 'r') scanf("%c", &entree);
    printf("lettre : %c\n", entree);
    printf("\n");
    return entree;
}

point_t* newPerso (int colonne, int ligne){
    point_t* np = malloc(sizeof(int)*2+sizeof(char));
    np->colonne = colonne; np->ligne = ligne; np->c_temp=' ';
    return np;
}

void deplacement (niveau_t* niveau,char entree){
            
    place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne,niveau->perso->c_temp);

    if(entree == 'z'){

        if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)!='$'&&
            lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)!='*' &&
             lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)!='#'){
        niveau->perso->c_temp=lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1);}

      if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)=='$' ||          //si +1 = caisse $ ou
         lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)=='*'){         //si +1 = caisse *
            if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-2)==' '){   //si +2 = vide
               niveau->perso->ligne--;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne-1,'$');        //place caisse validée
            }
            else if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-2)=='.'){//si +2 = rangement
               niveau->perso->ligne--;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne-1,'*');        //place caisse validée
            }
      }else if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)==' ' ||
               lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1)=='.'){   //si +1 = vide
      niveau->perso->ligne--;                                                                      //déplace perso
      }
   }

    if(entree == 's'){

        if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)!='$' &&
            lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)!='*'&&
             lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)!='#'){
        niveau->perso->c_temp=lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1);}

      if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)=='$' ||          //si +1 = caisse $ ou
         lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)=='*'){         //si +1 = caisse *
            if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+2)==' '){   //si +2 = vide
               niveau->perso->ligne++;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne+1,'$');        //place caisse validée
            }
            else if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+2)=='.'){//si +2 = rangement
               niveau->perso->ligne++;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne+1,'*');        //place caisse validée
            }
      }else if(lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)==' ' ||
               lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1)=='.'){   //si +1 = vide
      niveau->perso->ligne++;                                                                      //déplace perso
      }

    }
    if(entree == 'q'){

        if(lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)!='$' &&
            lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)!='*'&&
             lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)!='#'){
        niveau->perso->c_temp=lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne);}

        if(lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)=='$' ||          //si +1 = caisse $ ou
         lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)=='*'){         //si +1 = caisse *
            if(lecture_du_terrain(niveau, niveau->perso->colonne-2, niveau->perso->ligne)==' '){   //si +2 = vide
               niveau->perso->colonne--;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne-1,niveau->perso->ligne,'$');        //place caisse validée
            }
            else if(lecture_du_terrain(niveau, niveau->perso->colonne-2, niveau->perso->ligne)=='.'){//si +2 = rangement
               niveau->perso->colonne--;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne-1,niveau->perso->ligne,'*');        //place caisse validée
            }
      }else if(lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)==' ' ||
               lecture_du_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne)=='.'){   //si +1 = vide
      niveau->perso->colonne--;                                                                      //déplace perso
      }

    }

    if(entree == 'd'){

        if(lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)!='$' &&
            lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)!='*' &&
             lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)!='#'){
        niveau->perso->c_temp=lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne);}

                if(lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)=='$' ||          //si +1 = caisse $ ou
         lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)=='*'){         //si +1 = caisse *
            if(lecture_du_terrain(niveau, niveau->perso->colonne+2, niveau->perso->ligne)==' '){   //si +2 = vide
               niveau->perso->colonne++;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne+1,niveau->perso->ligne,'$');        //place caisse validée
            }
            else if(lecture_du_terrain(niveau, niveau->perso->colonne+2, niveau->perso->ligne)=='.'){//si +2 = rangement
               niveau->perso->colonne++;                                                             //déplace perso
               place_sur_terrain(niveau,niveau->perso->colonne+1,niveau->perso->ligne,'*');        //place caisse validée

            }
      }else if(lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)==' ' ||
               lecture_du_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne)=='.'){   //si +1 = vide
      niveau->perso->colonne++;                                                                      //déplace perso
      }
    }
    if(niveau->perso->c_temp=='.')place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne,'+');
    else place_sur_terrain(niveau,niveau->perso->colonne,niveau->perso->ligne,'@');
}

//exo3
int niveau_termine (niveau_t* niveau){
    int cpt = 0;
    for(int i=0; i<=niveau->nb_lignes+1; i++){
        for(int j=0; j<=niveau->nb_colonnes; j++){
            if(lecture_du_terrain(niveau,i,j) == '$'){
                cpt++;
            }
            
        }
    }
    //printf("%d\n",cpt);
    if(cpt>0) return 0; 
    else return 1;
}

//exo4
void affichage_score(niveau_t* niveau){
    system("clear");
    if(niveau_termine(niveau) == 1){
        printf("Win !\n");
    }
}

int lecture_du_score (int quel_niveau){
    int score = 0;
    char fichierScore[50];
    sprintf(fichierScore, "./niveaux/score_%i",quel_niveau);
    FILE* fichier = fopen(fichierScore,"r");
    fscanf(fichier, "%d", &score);
    fclose(fichier);
    
    return score;
}

void ecriture_du_score (int quel_niveau,int score){
    char niveau[50];
    sprintf(niveau, "./niveaux/score_%d",quel_niveau);
    FILE* fichier = fopen(niveau,"w");
    fprintf(fichier,"%i",score);
    fclose(fichier);
}

//exo5
char* nom_du_joueur (void){
    char * pseudo=malloc(sizeof(char)*8);
    printf("Quel est ton pseudo ? (8 caractères max.) ");
    scanf ("%s", pseudo);

    if (strlen(pseudo)>8||strlen(pseudo)==0){   
        printf ("Ta saisie est invalide !\n\n");
        free(pseudo);
        return pseudo=nom_du_joueur();
    }else{
       return pseudo; 
    } 
}

void ecriture_du_score_multi(int quel_niveau,int score){
    char niveau[50];
    sprintf(niveau, "./niveaux/score_multi_%d",quel_niveau);
    FILE* fichier = fopen(niveau,"w");
    fprintf(fichier,"%s : %i",nom_du_joueur(),score);
    fclose(fichier);
}


//exo6
niveau_t* copie_du_niveau (niveau_t* niveau){
    niveau_t* copie = niveau;
    return copie;
}

historique_t* intitialise_historique (niveau_t* niveau, int taille){
	historique_t* hist = malloc(sizeof(historique_t));
    hist->tableau = malloc(sizeof(niveau_t)* taille);
    hist->taille = taille;
    hist->idx = 0;
    return hist;
}

void affichage_historique (historique_t* hist){
    if(hist->idx < hist->taille) for(int i = 0; i < hist->idx; i++) affichage_niveau(hist->tableau[i]);
    else for(int i = 0; i < hist->taille; i++) affichage_niveau(hist->tableau[i]);
}

void liberation_historique (historique_t* hist){
    for(int i = 0; i<hist->taille; i++) free(hist->tableau[i]);
    free(hist->tableau);
    free(hist);
}

void sauvegarde_un_coup (historique_t* hist, niveau_t* niveau){
    free(hist->tableau[0]);
    for(int i = 1; i<hist->taille; i++) hist->tableau[i-1] = hist->tableau[i];
    hist->tableau[hist->taille-1] = niveau;
}

niveau_t* coup_precedent (historique_t* hist){
    niveau_t* flip = hist->tableau[hist->taille-1];
    hist->idx--;
    return flip;
}
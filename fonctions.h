//exo1
niveau_t* nouveau_niveau(int nb_colonnes,int nb_lignes);
void place_sur_terrain (niveau_t* niveau,int colonne,int ligne,char car);
char lecture_du_terrain (niveau_t* niveau,int colonne,int ligne);
void initialise_le_terrain (niveau_t* niveau);
void affichage_niveau (niveau_t* niveau);
niveau_t* lecture_du_niveau(int quel_niveau);
void liberation_du_niveau (niveau_t* niveau);

//exo2
void suivant();
char entree_du_joueur (void);
char menuJeu (void);
void regles(void);
void bestScore(void);
void meilleurScore(int quel_niveau);
char choixNiveau(void);
void deplacement (niveau_t* niveau,char direction);
point_t* newPerso (int colonne, int ligne);

//exo3
int niveau_termine (niveau_t* niveau);

//exo4
void affichage_score(niveau_t* niveau);
int lecture_du_score (int quel_niveau);
void ecriture_du_score (int quel_niveau,int score);

//exo5
char* nom_du_joueur (void);
void ecriture_du_score_multi(int quel_niveau,int score);

//exo6
niveau_t* copie_du_niveau (niveau_t* niveau);
void sauvegarde_un_coup (historique_t* hist, niveau_t* niveau);
niveau_t* coup_precedent (historique_t* hist);
historique_t* intitialise_historique (niveau_t* niveau, int taille);
void affichage_historique (historique_t* hist);
void liberation_historique (historique_t* hist);
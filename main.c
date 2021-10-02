#include "main.h"

int main(void) {

	char menu;
	menu = ' ';
	niveau_t* niveau;
	/*int taille;
	taille = 5;
	historique_t* hist;*/
	int score;
	score=0;
	int niv;
    
	// /* code */
	system("clear");
	do {
		//hist = intitialise_historique(niveau,taille);
		menu = menuJeu();
		if(menu == '1'){	
			niv = '0' - choixNiveau();
   			niveau = lecture_du_niveau(niv);
    		affichage_niveau(niveau);
			do{
				char entree;
				entree = entree_du_joueur();
				if(entree == 'r'){
					niveau = lecture_du_niveau(niv);
    				affichage_niveau(niveau);
				}
				else {
				/*if(entree == 'a'){
					score--;
					affichage_niveau(coup_precedent(hist));
				}*/
					deplacement(niveau, entree);
					score++;	
					affichage_niveau(niveau);
				}
				//sauvegarde_un_coup(hist,niveau);
				niveau_termine(niveau);
			} while(niveau_termine(niveau) != 1);
			affichage_score(niveau);
			printf("Score : %d\n",score);
			if(lecture_du_score(niv) > score) ecriture_du_score(niv,score);
			ecriture_du_score_multi(niv,score);		
			system("clear");	
		}
		if(menu == '2'){
			regles();
			suivant();
			system("clear");
		}
	} while(menu != '3');
	system("clear");
	return 0;
}
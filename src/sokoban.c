#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/gestion_menu.h"
#include "../inc/score.h"
//-1 : mur, 1 :pers, 2 :caisse, 0 : vide, 3:objectif, 5:caisse sur objectif ,4:perso sur objectif


int main(){
	int **tab=malloc(sizeof(int*)*20);  //creation du plateau de jeu de taille 20x20
	if(tab==NULL){
		printf("probleme tab");
	}
	for(int i=0;i<20;i++){
		tab[i]=malloc(sizeof(int)*20);
		if(tab[i]==NULL){
			printf("probleme tab[i]");
			for(int k;k<i;k++){
				free(tab[k]);
			}
			free(tab);
		}

	}

	int *score_tab=malloc(sizeof(int)*10);   //creation du tableau de scores 
	if(score_tab==NULL){
		printf("probleme score_tab");
	}

	//fichier_score();  //si le fichier score.txt a été supprimé, utiliser cette ligne pour le creer 
	get_best_score(score_tab);  //recuperation des scores stockes dans le fichier score.txt


	menu(tab, score_tab);  // on lance le menu
	
	
	return 0;
}
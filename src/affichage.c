#include <stdio.h>
#include <stdlib.h>


#include "../inc/affichage.h"

//fonction affichant le plateau
void affichage(int **plateau, int taille){

	for(int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			if(plateau[i][j]==-1){
				printf("#");
			}
			else if(plateau[i][j]==1 || plateau[i][j]==4){
				printf("P");
			}
			else if(plateau[i][j]==0){
				printf(" ");
			}
			else if(plateau[i][j]==2){
				printf("c");
			}
			else if(plateau[i][j]==5){
				printf("ç");
			}
			else{
				printf("I");
			}
		}
		printf("\n");
	}
}


//fonction affichant le score
void affiche_score(int best_score, int score){
	printf("Score : %d            Best score : %d\n\n",score,best_score );
}
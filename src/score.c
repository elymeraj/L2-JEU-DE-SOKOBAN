#include <stdio.h>
#include <stdlib.h>

//fonction renvoyant le score
int calcule_score(int nb_tours, int temps, int num_niveau){
	if (temps!=0){  //si le jeu a déjà commencé
		int score=1000*num_niveau-(temps*nb_tours);
		if(score<0){  //le score ne descend jamais en dessous de 0
			return 0;
		}
		return score;
	}
	return 1000*num_niveau;  //si le jeu vient de commencer, on affiche ce score standard
	
}

//cette fonction récupère les scores dans le fichier score.txt
//et les range dans un tableau
void get_best_score(int *tab){
	FILE *f=fopen("./score.txt", "r");
	if (f==NULL){
		exit(-1);
	}

	int a_jeter;

	for(int i=1;i<11;i++){
		fscanf(f, "Map %d : %d\n",&a_jeter,&tab[i-1]);
	}

	fclose(f);
}

//cette fonction met à jour le fichier score.txt si le best score a été battu
//la valeur est aussi changé dans le tableau
void maj_best_score(int* score_tab, int best_score, int num_niveau){
	FILE *f=fopen("./score.txt", "w");
	if (f==NULL){
		exit(-1);
	}

	score_tab[num_niveau-1]=best_score;

	for(int i=1;i<11;i++){
		fprintf(f, "Map %d : %d\n",i,score_tab[i-1]);
	}

	fclose(f);
}

//fonction créant un fichier score.txt utile s'il a été supprimé
void fichier_score(){
	FILE *f=fopen("./score.txt", "w");
	if (f==NULL){
		exit(-1);
	}

	int score=0;

	for(int i=1;i<11;i++){
		fprintf(f, "Map %d : %d\n",i,score);
	}

	fclose(f);
}
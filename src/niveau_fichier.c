#include <stdio.h>
#include <stdlib.h>

#include "../inc/niveau_fichier.h"

//fonction permettant de sauvegarder la progression dans le fichier save.txt
//elle note le temps auquel la sauvegarde a été faite, le nombre de tours écoulés durant la partie, et le niveau
int save(int** plateau, int niveau, int time, int nb_tours){
	FILE *f=fopen("./maps/save.txt", "w");  //on ouvre le fichier en écriture
	if(f==NULL){
		return -1;
	}
	fprintf(f,"%d %d %d  ",niveau, time, nb_tours);  //on note d'abord le niveau, le temps et le nombre de tours
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			fprintf(f,"%d ",plateau[i][j]);   
		}
	}
	fclose(f);
	return 1;
}

//fonction permettant de charger un niveau
void charger(int *num_niveau, int **plateau, int *x, int *y, int charge_save, int *time, int *nb_tours){

	for(int i=0;i<20;i++){   //on réinitialise le tableau
		for(int j=0;j<20;j++){
			plateau[i][j]=0;
		}
	}      

	FILE *f;
	if(charge_save==1){  //si charge_save == 1 alors on charge à partir de la sauvegarde
		f=fopen("./maps/save.txt", "r");
		if(f==NULL){
			exit(-1);
		}
		fscanf(f,"%d %d %d  ",num_niveau, time, nb_tours);  //permet de trouver les données dans la sauvegarde
	}
	else{
		printf("%d\n", *num_niveau);
		char fichier[30];
		sprintf(fichier, "./maps/map%d.txt", *num_niveau);  //permet d'avoir le nom du fichier contenant la map du niveau voulu

		f=fopen(fichier, "r");  
		if(f==NULL){
			exit(-1);
		}
	}
	for(int i=0;i<20;i++){   //on charge la map dans le tableau
		for(int j=0;j<20;j++){
			fscanf(f,"%d ",&plateau[i][j]);
			if(plateau[i][j]==1){  //on rentre les coordonnées du personnage
				*x=i;
				*y=j;
			}
		}
	}
	fclose(f);


}


//permet de savoir si un fichier existe
int if_file_exist(char *fichier){
	FILE *f=fopen(fichier,"r");
	if (f==NULL){
		return -1;
	}
	fclose(f);
	return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/gestion_menu.h"
#include "../inc/timer.h"
#include "../inc/affichage.h"
#include "../inc/deplacement.h"
#include "../inc/niveau_fichier.h"
#include "../inc/score.h"

//fonction affichant le menu et permettant au joueur de choisir ce qu'il veut faire
void menu(int ** plateau, int *score_tab){

	system("clear");
	printf("----------SOKOBAN----------\n\n");
	printf("1. Nouvelle partie\n2. Charger partie\n3. Règles\n4. Quitter le jeu\n");

	char choix;

	do{
		//scanf("%c%*c",&choix);
		choix=getchar();
		if(choix == '1'){
			lance_niveau(1, plateau,0, score_tab);  //lance le premier niveau
		}
		else if(choix == '2'){
			if(if_file_exist("./maps/save.txt")==1){ //si le fichier de sauvegarde existe, on charge
				lance_niveau(0,plateau,1,score_tab);
			}
			else{
				printf("Il n'y a pas de fichier de sauvegarde.\n"); //sinon le joueur doit faire une autre choix
				choix=5;
			}
		}
		else if(choix == '3'){  //affiche les règles
			regles();
		}
		else if(choix=='4'){ //quitte le programme
			for(int i=0;i<20;i++){
				free(plateau[i]);
			}
			free(plateau);   
			free(score_tab); //liberation de l'espace memoire
			exit(0);
		}
	}while(choix!='1' || choix!='2');
}

//focntion permettant de lancer le niveau voulue
void lance_niveau(int num_niveau, int **plateau, int charger_niveau, int *score_tab){

	int x,y;  //variables acceuillants les coord du perso
	int complete=0; //permet de savoir quand arrêter le niveau
	int nb_tours=0;
	int decalage=0;  //lorsqu'on charge une partie permet de savoir combien de secondes s'étaient écoulés
	int score;
	int diff_int; //ici est stocké la différence de temps entre le moment où la partie a commencé et le moment présent
	char input;
	int sauvegarde=0;

	if (charger_niveau==1){  //charge le niveau sauvegarder

		charger(&num_niveau, plateau, &x,&y,1,&decalage,&nb_tours);
	}
	else{
		charger(&num_niveau, plateau, &x,&y,0,&decalage,&nb_tours);
	}


	time_t start=get_time();  //on stocke le moment où on a commencé la partie

	while(complete==0){  
		
		scanf("%*c");  //dump l'input de la touche entrée

		system("clear");

		printf("Niveau : %d\n", num_niveau);

		affiche_timer(start, &diff_int, decalage);  //on affiche le temps

		score=calcule_score(nb_tours,diff_int,num_niveau); //on calcule le score
		affiche_score(score_tab[num_niveau-1], score); //on l'affiche

		affichage(plateau, 20); //on affiche le plateau

		if(sauvegarde==1){
			printf("La sauvegarde a été effectuée\n");
			sauvegarde=0;
		}
		else if(sauvegarde==-1){
			printf("La sauvegarde a échouée\n");
			sauvegarde=0;
		}

		input=getchar();//on demande au joueur d'agir 
		if(input=='i'){  //le joueur sauvegarde
			sauvegarde=save(plateau, num_niveau, diff_int, nb_tours);
		}
		else if(input=='r'){  //le joueur restart le niveau
			lance_niveau(num_niveau, plateau, charger_niveau, score_tab);
		}
		else if(input=='m'){   //le joueur retourne au menu
			menu(plateau, score_tab);
		}
		else if(input=='p' && num_niveau<10){  //le joueur passe au niveau suivant
			lance_niveau(num_niveau+1, plateau,0,score_tab);
		}
		else if(input=='o' && num_niveau>1){  //le joueur retourne au niveau précédant
			lance_niveau(num_niveau-1, plateau,0,score_tab);
		}
		else{ //on appelle la fonction déplacement qui va se charger des déplacements
			deplacememt(input, plateau,20,&x,&y,&nb_tours);
		}

		complete=detect_fin(plateau, 20);  //on vérifie que le niveau n'est pas fini
	}
	//une fois le niveau fini(peut importe le résultat)
	affiche_timer(start, &diff_int, decalage); //on affiche le temps total
	affiche_score(score_tab[num_niveau-1],score); //on affiche le score

	if(score>score_tab[num_niveau-1] && complete==1){  //on vérifie si le joueur a battu le meilleur score
		maj_best_score(score_tab,score,num_niveau);
		printf("Nouveau meilleur score !!\n\n");
	}
	fin_niveau(complete,num_niveau,plateau,score_tab);

}

//fonction gérant la transition entre les niveaux
void fin_niveau(int fin,int num_niveau, int **plateau, int *score_tab){
	char choix_fin;
	scanf("%*c");   //eviter que le texte s'affiche deux fois du au fait qu'on doive appuyer sur entrée
	do{
		if(fin==1){  //cas où le joueur a gagné
			if(num_niveau<10){ //le joueur est avant le dernier niveau
				printf("----------Vous avez terminé le niveau----------\n\n");
				printf("Que souhaitez-vous faire ? :\n");
				printf("1. Passer au niveau suivant\n2. Retourner au menu\n");
				choix_fin=getchar();
				if(choix_fin=='1'){
					lance_niveau(num_niveau+1, plateau,0,score_tab); //on lance le niveau suivant 
				}
			}
			else{
				printf("----------Bravo !!! Vous avez terminé le jeu----------\n\n");
				printf("Que souhaitez-vous faire ? :\n");
				printf("1. Revenir au premier niveau\n2. Retourner au menu\n");
				choix_fin=getchar();
				if(choix_fin=='1'){
					lance_niveau(1, plateau,0,score_tab); //on revient au premier niveau
				}
			}
		}
		else if(fin==-1){ //cas où le joueur a perdu 
			printf("----------Vous avez perdu----------\n\n");
			printf("Que souhaitez-vous faire ? :\n");
			printf("1. Retenter le niveau\n2. Retourner au menu\n");
			choix_fin=getchar();
			if(choix_fin=='1'){
				lance_niveau(num_niveau, plateau,0,score_tab); //on relance le même niveau
			}
		}

		if(choix_fin=='2'){
			menu(plateau, score_tab);  //on accède au menu
		}
	}while(choix_fin!='1' || choix_fin!='2');
}

void regles(){

	system("clear");
	printf("------------------------Bienvenu au jeu Sokoban-------------------------\n\n");
	printf("Le but est de placer l'ensemble des caisses, représentées par c, sur les indices I.\n\n");
	printf("Pour cela, bougez votre personnage, signifié par l'icône P, à l'aide des touches Z,Q,S,D permettant respectivement d'aller en haut, à gauche, en bas et à droite.\n\n");
	printf("Vous allez être confronté à 10 niveaux allant dans un ordre croissant de difficulté.\n\n");
	printf("Les niveaux seront chronométrés. Essayez d'en venir à bout rapidement et avec le moins de coup possible pour avoir le meilleur score possible.\n\n");
	printf("Vous pouvez retrouver vos meilleurs scores dans le fichier score.txt.\n\n");
	printf("Vous pouvez sauvegarder à tout moment en appuyant sur la touche i puis entrée.\n\n");
	printf("Vous pouvez recommencer un niveau si vous êtes bloqué en appuyant sur la touche r puis entrée.\n\n");
	printf("Vous pouvez revenir au menu à tout moment en appuyant sur la touche m puis entrée.\n\n");
	printf("Vous pouvez passer au niveau suivant en appuyant sur p puis entrée.\n\n");
	printf("Vous pouvez retourner au niveau précédant en appuyant sur o puis entrée.\n\n");
	printf("----------SOKOBAN----------\n\n");
	printf("1. Nouvelle partie\n2. Charger partie\n3. Règles\n4. Quitter le jeu\n");


}
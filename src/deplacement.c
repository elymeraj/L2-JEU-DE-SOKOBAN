#include <stdio.h>
#include <stdlib.h>

#include "../inc/affichage.h"
#include "../inc/deplacement.h"

//fonction renvoyant si le deplacement d'une entite est possible dans une telle direction
//si entite = 1 alors on s'interesse au personnage si = a 2 il s'agit d'une caisse
//x,y sont les coordonnees de l'entite dans le tableau
//renvoie 1 si deplacement possible, 0 sinon
int deplacement_possible(int **plateau, int taille, int x, int y, char direc, int entite){ 
	if (direc=='z'){ //haut
		if (x>0){  //on verifie qu'on est pas aux limites du tableau pour ne pas avoir d'erreur
			if(entite!=2 && (plateau[x-1][y]==2 || plateau[x-1][y]==5)){    
				//si l'entite etudié est le personnage et qu'il essaie de pousser une caisse on verifie si la caisse peut bouger
				return deplacement_possible(plateau, taille, x-1,y,'z',2);  //pour cela on refait appelle à cette focntion avec entite = 2
			}
			else if(plateau[x-1][y]==0 || plateau[x-1][y]==3 ){  
				return 1;  //si le perso se déplace vers une case vide ou un objectif, le déplacement est possible
			}
		}
	}
	else if (direc=='s'){ //bas
		if (x<taille-1){
			if(entite!=2 && (plateau[x+1][y]==2 || plateau[x+1][y]==5) ){
				return deplacement_possible(plateau,taille, x+1,y,'s',2);
			}
			else if(plateau[x+1][y]==0 || plateau[x+1][y]==3 ){
				return 1;
			}
		}
	}
	else if (direc=='d'){ //droite
		if (y<taille-1){
			if(entite!=2 && (plateau[x][y+1]==2 || plateau[x][y+1]==5) ){
				return deplacement_possible(plateau,taille, x,y+1,'d',2);
			}
			else if(plateau[x][y+1]==0 || plateau[x][y+1]==3 ){
				return 1;
			}
		}
	}
	else{ //direct=='g'
		if (y>0){
			if(entite!=2 && (plateau[x][y-1]==2 || plateau[x][y-1]==5)){
				return deplacement_possible(plateau,taille,x,y-1,'q',2);
			}
			else if(plateau[x][y-1]==0 || plateau[x][y-1]==3 ){
				return 1;
			}
		}
	}
	return 0;

}

//cette fonction met à jour les valeurs des cases du tableau selon les dépalcements effectués
//elle prend en argument, le plateau, les coordonnées du perso
//depla_x indique si le perso bouge de façon verticale(-1 s'il monte, +1 s'il descend)
//depla_y indique si le perso bouge de façon horizontale(-1 s'il va à gauche, +1 s'il va à droite)
void maj_carte(int ** plateau, int *x, int *y, int depla_x, int depla_y){
	int val; 

	int ajout_x=0, ajout_y=0;   

	if(depla_x<0){ajout_x=-1;}
	else if(depla_x>0){ajout_x=1;}

	if(depla_y<0){ajout_y=-1;}
	else if(depla_y>0){ajout_y=1;}

	plateau[*x][*y]-=1;  //la case où était le perso devient vide

	if(plateau[*(x)+depla_x][*(y)+depla_y]==5){ //cas où la caisse est sur l'objectif et que le perso va dessus
		plateau[*(x)+depla_x][*(y)+depla_y]=4;  //la case où le personnage se mouvoit contient maintenant le perso et l'objectif
		plateau[*(x)+depla_x+ajout_x][*(y)+depla_y+ajout_y]+=2;  //la casse d'après contient en plus la caisse poussée
	}
	else if(plateau[*(x)+depla_x][*(y)+depla_y]==3){  //cas où le personnage va sur l'objectif vide
		plateau[*(x)+depla_x][*(y)+depla_y]=4;   //la case où le personnage se mouvoit contient maintenant le perso et l'objectif
	}
	else{  //cas ou le perso bouge une caisse ou se deplace dans une casse vide
		val=plateau[*(x)+depla_x][*(y)+depla_y];  //on conserve la valeur de la casse ou l'on souhaite aller
		plateau[*(x)+depla_x][*(y)+depla_y]=1;  //le perso bouge dans la direction souhaité occupant seul une case
		plateau[*(x)+depla_x+ajout_x][*(y)+depla_y+ajout_y]+=val;	
	}
	*x+=depla_x;	//mise à jour coordonnees du perso
	*y+=depla_y;

}

//cette fonction s'oocupe de gérer le déplacement du personnage dans le tableau
//cette fonction sert aussi à compter le nombre de tours utiles pour le calcul du score
void deplacememt(int direc, int ** plateau, int taille, int *x, int *y, int *nb_tours){

	if (direc=='z'){
		if(deplacement_possible(plateau, taille, *x, *y, direc, 1)==1){  // on verifie si le deplacement est possible

			maj_carte(plateau, x, y, -1, 0);  //on met à jour le tableau
			*nb_tours=*nb_tours+1;  //on incrémente de un le nombre de tours

		}
	}
	else if (direc=='s'){
		if(deplacement_possible(plateau, taille, *x, *y, direc, 1)==1){

			maj_carte(plateau, x, y, 1, 0);
			*nb_tours=*nb_tours+1;

		}
	}
	else if (direc=='q'){
		if(deplacement_possible(plateau, taille, *x, *y, direc, 1)==1){

			maj_carte(plateau, x, y, 0, -1);
			*nb_tours=*nb_tours+1;
		}
	}
	else if (direc=='d'){
		if(deplacement_possible(plateau, taille, *x, *y, direc, 1)==1){

			maj_carte(plateau, x, y, 0, 1);
			*nb_tours=*nb_tours+1;

		}
	}
	
}

//cette fonction sert à détecter une fin de jeu
//elle renvoie 1 si tous les objectifs ont été complétés
//elle renvoie 0 si la partie est toujours en cours
//elle renvoie -1 si le joueur est bloqué
int detect_fin(int **plateau, int taille){
	int nb_indices_restants=0;
	int bloque;
	for(int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			if(plateau[i][j]==4 || plateau[i][j]==3){
				nb_indices_restants++;  //on compte le nombre d'indices restants sur la map
			}
			else if (plateau[i][j]==1 ){
				bloque=0;
				//si le perso peut se déplacer dans une direction le compteur est incrémenté
				bloque+=deplacement_possible(plateau, taille, i, j, 'z', 1);
				bloque+=deplacement_possible(plateau, taille, i, j, 's', 1);
				bloque+=deplacement_possible(plateau, taille, i, j, 'q', 1);
				bloque+=deplacement_possible(plateau, taille, i, j, 'd', 1);
				if (bloque==0){   //si le compteur est égal à 0, le joueur ne peut bouger dans une aucune direction
					return -1;   //il  est bloqué, fin de jeu
				}
			}
			
		}
	}
	if(nb_indices_restants==0){return 1;}  //s'il n'y a plus aucun indice sur la map alors le joueur a gagné
	return 0;
}
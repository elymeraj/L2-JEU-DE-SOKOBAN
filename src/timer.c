#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/timer.h"

//renvoie une variable time_t contenant le temps au moment où la fonction a été appelé
time_t get_time(){
	time_t temps;
	time(&temps);
	return temps;
}

void affiche_timer(time_t start, int *diff_int, int decalage){
	time_t current_time=get_time();  
	double diff=difftime(current_time, start); //on calcule la difference de temps entre start et current time et renvoie la difference en secondes
	*diff_int=(int) diff + decalage;
	int s, min, h;
	h=*diff_int/3600;   //on converti la différence en heures
	min=(*diff_int%3600)/60;  //on converti la différence en minutes
	s=*diff_int%3600%60;  //on converti la différence en secondes
	printf("Timer : %02d:%02d:%02d\n",h, min, s);  //on affiche le timer
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef TIMER	
#define TIMER

time_t get_time();  //stocke la valeur du temps dans une variable time_t à l'instant où la fonction est appelé
void affiche_timer(time_t start, int *diff_int, int decalage); //calcule la difference de temps entre le debut de la partie et le moment où cette fonction est appelé et l'affiche


#endif 
#include <stdio.h>
#include <stdlib.h>

#ifndef SCORE
#define SCORE


int calcule_score(int nb_tours, int temps, int num_niveau);
void get_best_score(int* tab);
void maj_best_score(int* score_tab, int best_score, int num_niveau);
void fichier_score();

#endif 
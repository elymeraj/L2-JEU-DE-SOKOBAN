#include <stdio.h>
#include <stdlib.h>

#ifndef FICHIER
#define FICHIER

int save(int** plateau, int niveau, int time, int nb_tours);
void charger(int *num_niveau, int **plateau, int *x, int *y, int charge_save, int *time, int *nb_tours);
int if_file_exist(char *fichier);


#endif
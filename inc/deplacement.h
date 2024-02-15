#include <stdio.h>
#include <stdlib.h>

#include "../inc/affichage.h"

#ifndef DEPLACEMENT	
#define DEPLACEMENT

int deplacement_possible(int **plateau, int taille, int x, int y, char direc, int entite);
void maj_carte(int ** plateau, int *x, int *y, int depla_x, int depla_y);
void deplacememt(int direc, int ** plateau, int taille, int *x, int *y, int *nb_tours);
int detect_fin(int **plateau, int taille);



#endif 
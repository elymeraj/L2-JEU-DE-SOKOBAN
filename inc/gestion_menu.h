#include <stdio.h>
#include <stdlib.h>

#ifndef MENU
#define MENU

void menu(int ** plateau, int *score_tab);
void lance_niveau(int num_niveau, int ** plateau,int charger_niveau, int *score_tab);
void fin_niveau(int fin,int num_niveau, int **plateau, int *score_tab);
void regles();




#endif 
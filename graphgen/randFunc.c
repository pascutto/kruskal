#include <time.h>
#include <math.h>
#include "randFunc.h"
#include "error.h"

int uniformDistributionInt(int min, int max) {
    return (int)((rand() / ((double)RAND_MAX + 1)) * (max - min)) + min;
}

double uniformDistributionDouble(double min, double max) {
    return (rand() / ((double)RAND_MAX + 1)) * (max - min) + min;
}

int* randomPermutation(int n) {
    int *tab; 
    tab = malloc(sizeof(int) * n);
    if (tab == NULL)
        error("Impossible d'allouer le tableau de la permutation.");

    int i;
    for (i = 0; i < n; ++i)
        tab[i] = i;

    for (i = 0; i < n; ++i) {
        int j = uniformDistributionInt(0, i + 1);
        int aux = tab[i];
        tab[i] = tab[j];
        tab[j] = aux;
    }

    return tab;
}

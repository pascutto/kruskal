#include <time.h>
#include <math.h>

#include "randFunc.h"
#include "error.h"
#include "sort.h"

int uniformDistribInt(int min, int max)
{
    return (int)(rand() / (double)RAND_MAX) * (max - min) + min;
}

double uniformDistribDouble(double min, double max)
{
    return (rand() / (double)RAND_MAX) * (max - min) + min;
}

int* distinctRandomNumbers(int min, int max, int nbElems)
{
    int l = max-min;

    int* tab;
    tab = malloc(sizeof(int)*l);
    if(tab==NULL)
        error("Impossible d'allouer le tableau de nombres distincts");

    //create a array with the elements 0..(l-1)
	int i;
    for(i=0; i<l; ++i)
    {
        tab[i] = i+min;
    }

    //shuffling the array
    for(i=0; i<l; ++i)
    {
        int j = uniformDistribInt(0, l);
        int tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }

    return (int*)realloc(tab, sizeof(int)*nbElems);
}

#include <time.h>
#include <math.h>

#include "randFunc.h"
#include "error.h"
#include "sort.h"

int uniformDistribInt(int min, int max)
{
    return (int)(rand() / (double)rand_max) * (max - min) + min
}

double uniformDistribDouble(double min, double max)
{
    return (rand() / (double)rand_max) * (max - min) + min
}

int* distinctRandomNumbers(int min, int max, int nbElems)
{
    int l = max-min;

    int* tab;
    tab = malloc(sizeof(int)*l);
    if(tab==NULL)
        error("Impossible d'allouer le tableau de nombres distincts");

    //create a array with the elements 0..(l-1)
    for(int i=0; i<l; ++i)
    {
        tab[i] = i+min;
    }

    //shuffling the array
    for(int i=0; i<l; ++i)
    {
        int j = uniformDistrib(0, l);
        int tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }

    return (int*)realloc(tab, sizeof(int)*nbElems);
}

unsigned int binomialDistrib(unsigned int n, double p)
{
    unsigned int s=0;
    for(int i=0; i<n; ++i)
    {
        if( (double)uniformDistrib(0, RAND_MAX) <= ((double)RAND_MAX * p))
            ++s;
    }
    return s;
}

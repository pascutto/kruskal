#include <time.h>
#include <math.h>

#include "randFunc.h"
#include "error.h"
#include "sort.h"

int uniformDistrib(int min, int max)
{
    static int init = 0;
    if(init==0)
    {
        srand((unsigned int)time(0));
        init = 1;
    }

    return rand()/((double)(RAND_MAX+1)/(double)(max-min))+min;
}

id* distinctRandomNumbers(id min, id max, id nbElems)
{
    id l = max-min;

    id* tab;
    tab = malloc(sizeof(id)*l);
    if(tab==NULL)
        error("Impossible d'allouer le tableau de nombres distincts");

    //create a array with the elements 0..(l-1)
    for(id i=0; i<l; ++i)
    {
        tab[i] = i+min;
    }

    //shuffling the array
    for(id i=0; i<l; ++i)
    {
        id j = uniformDistrib(0, l);
        id tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }

    return (id*)realloc(tab, sizeof(id)*nbElems);
}

unsigned int binomialDistrib(unsigned int n, double p)
{
    unsigned int s=0;
    for(id i=0; i<n; ++i)
    {
        if( (double)uniformDistrib(0, RAND_MAX) <= ((double)RAND_MAX * p))
            ++s;
    }
    return s;
}

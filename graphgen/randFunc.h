#ifndef RANDFUNC_H_INCLUDED
#define RANDFUNC_H_INCLUDED

#include "stdlib.h"

typedef size_t id;

///uniform integer distribution between min (included) and max (excluded)
int uniformDistribInt(int min, int max);

double uniformDistribDouble(double min, double max);

///return an array of nbElems distinct random numbers between min (included) and max (excluded)
int* distinctRandomNumbers(int min, int max, int nbElems);


#endif // RANDFUNC_H_INCLUDED

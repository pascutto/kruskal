#ifndef RANDFUNC_H_INCLUDED
#define RANDFUNC_H_INCLUDED

#include "stdlib.h"

typedef size_t id;

///uniform integer distribution between min (included) and max (excluded)
int uniformDistrib(int min, int max);

///return an array of nbElems distinct random numbers between min (included) and max (excluded)
id* distinctRandomNumbers(id min, id max, id nbElems);

///return a random number following a binomial distribution
unsigned int binomialDistrib(unsigned int n, double p);

#endif // RANDFUNC_H_INCLUDED

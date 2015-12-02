#ifndef RANDFUNC_H_INCLUDED
#define RANDFUNC_H_INCLUDED

#include "stdlib.h"

int uniformDistributionInt(int min, int max);

double uniformDistributionDouble(double min, double max);

int* randomPermutation(int n);

#endif // RANDFUNC_H_INCLUDED

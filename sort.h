#ifndef _SORT_HEADER_
#define _SORT_HEADER_

#include "graph.h"

void sort(edge* v, int length);
void swap(edge* v, int i, int j);
void insertion_sort(edge* v, int left, int right);
void quick_sort(edge* v, int left, int right);

#endif

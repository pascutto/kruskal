#ifndef _SORT_HEADER_
#define _SORT_HEADER_

#include "graph.h"

void test_sort(edge* v, int length, int minLength);
void sort(edge* v, int length);
void swap(edge* v, int i, int j);
void insertion_sort(edge* v, int left, int right);
void quick_sort(edge* v, int left, int right, int minLength);
int median_of_three(edge* v, int left, int right);
int partition(edge* v, int left, int right);

// BOUNDS
int quick_sort_bound(edge* v, int left, int right, int minLength);
int insertion_sort_bound(edge* v, int left, int right);
int sort_bound(edge* v, int length);

#endif

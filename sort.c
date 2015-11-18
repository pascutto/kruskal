#include <time.h>
#include <stdlib.h>
#include "sort.h"

const int kMinLength = 100;

void swap(edge* v, int i, int j) {
	edge aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

void quick_sort(edge* v, int left, int right) {
	if (left < right) {
		if (right - left + 1 < kMinLength)
			insertion_sort(v, left, right);
		else {
			int r = rand() % (right - left + 1) + left;
			swap(v, left, r);
			int p = partition(v, left, right);
			quick_sort(v, left, p-1);
			quick_sort(v, p+1, right);
		}
	}
}

int partition(edge* v, int left, int right) {
	edge pivot = v[left]; 
	int i = left + 1;
	int j;
	for(j = left + 1; j <= right; j++)
		if (v[i].w > pivot.w) {
			swap(v, i, j);
			i++;
		}
	swap(v, left, i);
	return i;	
}

void insertion_sort(edge* v, int left, int right) {
	int i;
	for(i = left; i <= right; i++) {
		int j = i;
		while (j > left && v[j - 1].w > v[j].w) {
			swap(v, j - 1, j);
			j--;
		}
	}
}

void sort(edge* v, int length) {
	srand(time(NULL));
	quick_sort(v, 0, length - 1);
}

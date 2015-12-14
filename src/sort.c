#include "sort.h"

const int kMinLength = 20;

void swap(edge* v, int i, int j) {
	edge aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

int median_of_three(edge* v, int left, int right) {
    int r1 = left;
    int r2 = (left + right) / 2;
    int r3 = right;

    if (v[r1].w > v[r2].w)
        swap(v, r1, r2);

    if (v[r2].w > v[r3].w)
        swap(v, r2, r3);

    if (v[r1].w > v[r2].w)
        swap(v, r1, r2);

    return r2;
}

void quick_sort(edge* v, int left, int right, int minLength) {
	if (left < right) {
		if (right - left + 1 < minLength)
			insertion_sort(v, left, right);
		else {
			int r = median_of_three(v, left, right);
			swap(v, right, r);
			int p = partition(v, left, right);
			quick_sort(v, left, p - 1, minLength);
			quick_sort(v, p + 1, right, minLength);
		}
	}
}

int quick_sort_bound(edge* v, int left, int right, int minLength) {
    return (right - left + 1) * (right - left + 1);
    /*
        Let N be the length of vector to be sorted.
        Worst case complexity: O(N^2) 
            see "The Worst Case Permutation for Median-of-Three Quicksort", Hannu Erkio, 
                The Computer Journal, Vol. 27, No. 3, 1984
        Average-case: if N > minlength - O(N * log(N)), otherwise - O(N^2)
    */
}

int partition(edge* v, int left, int right) {
	edge pivot = v[right]; 
	int i = left;
    int j;
	for (j = left; j < right; j++)
		if (v[j].w <= pivot.w) {
			swap(v, i, j);
			i++;
		}
	swap(v, right, i);
	return i;	
}

void insertion_sort(edge* v, int left, int right) {
	int i;
	for (i = left; i <= right; i++) {
		edge x = v[i];
		int j = i;
		while (j > left && v[j - 1].w > x.w) {
			v[j] = v[j - 1];
			j--;
		}
		v[j] = x;
	}
}

int insertion_sort_bound(edge* v, int left, int right) {
    return (right - left + 1) * (right - left + 1);
    /* 
        Let N be the length of the vector to be sorted.
        Complexity: O(N^2)
    */
}

void test_sort(edge* v, int length, int minLength) {
    quick_sort(v, 0, length - 1, minLength);
}

void sort(edge* v, int length) {
	quick_sort(v, 0, length - 1, kMinLength);
}

int sort_bound(edge* v, int length) {
    return length * length;
}

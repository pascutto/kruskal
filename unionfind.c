#include "error.h"
#include "unionfind.h"
#include <stdlib.h>
#include <stdio.h>

unionfind new_uf(int n) {
	unionfind* uf = NULL;
	uf = malloc(sizeof(unionfind));
	check_alloc(uf);
	
	int* parent = NULL;
    parent = malloc(n * sizeof(int));
	check_alloc(parent);
	
	int* rank = NULL;
	rank = malloc(n * sizeof(int));
	check_alloc(rank);

	int i;
	for(i = 0; i < n; i++) {
		parent[i] = -1;
		rank[i] = 0;
	}
	uf->parent = parent;
	uf->rank = rank;
	uf->n = n;
	return *uf;
}

int find(unionfind* uf, int x) {
	if (uf->parent[x] == -1)
		return x;
	return (uf->parent[x] = find(uf, uf->parent[x]));
}

int merge(unionfind* uf, int x, int y) {
	int rx = find(uf, x);
	int ry = find(uf, y);
	if (rx == ry) 
		return 0;
	if (uf->rank[rx] < uf->rank[ry]) {
		uf->rank[ry] += uf->rank[rx];
		uf->parent[rx] = ry;
	}
	else {
		uf->rank[rx] += uf->rank[ry];
		uf->parent[ry] = rx;
	}
	return 1;
}

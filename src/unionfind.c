#include "error.h"
#include "unionfind.h"
#include <stdlib.h>
#include <stdio.h>

int log2(int x) {
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
}

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

int new_uf_bound(int n) {
    return n;
}

int find(unionfind* uf, int x) {
	if (uf->parent[x] == -1)
		return x;
	return (uf->parent[x] = find(uf, uf->parent[x]));
}

int find_bound(unionfind* uf, int x) {
    return log2(uf->n) / log2(log2(uf->n)); 
    /*
        Worst-case complexity: O(log(n) / log(log(n)))
            see "On The Single-Operation Worst-Case Time Complexity of The Disjoint Set Union Problem", Norbert Blum, 
                SIAM J. Comput., Vol. 15, No. 4, November 1986
        Amortized complexity: O(alpha(m, n)) where m is the total number of operations
            see "Efficiency of a Good But Not Linear Set Union Algorithm", Robert Endre Tarjan, 
                Journal of Association for Computing Machinery, Vol. 22, No. 2. April 1975
    */
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

int merge_bound(unionfind* uf, int x, int y) {
    return find_bound(uf, x) + find_bound(uf, y);
}

void free_uf(unionfind* uf) {
    free(uf->parent);
    free(uf->rank);
}

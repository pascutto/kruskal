#include "unionfind.h"

int find(int* parent, int x) {
	if (parent[x] == -1)
		return x;
	return (parent[x] = find(parent, parent[x]));
}

int merge(int* parent, int* rank, int x, int y) {
	int rx = find(parent, x);
	int ry = find(parent, y);
	if (rx == ry) 
		return 0;
	if (rank[x] < rank[y])
		parent[rx] = ry;
	else 
		parent[ry] = rx;
	return 1;
}

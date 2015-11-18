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
	if (rank[rx] < rank[ry]) {
		rank[ry] += rank[rx];
		parent[rx] = ry;
	}
	else {
		rank[rx] += rank[ry];
		parent[ry] = rx;
	}
	return 1;
}

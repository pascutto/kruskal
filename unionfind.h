#ifndef _UNIONFIND_HEADER_
#define _UNIONFIND_HEADER_

typedef struct {
	int n;
	int* parent;
	int* rank;
} unionfind;

unionfind new_uf(int n);
int find(unionfind* uf, int x);
int merge(unionfind* uf, int x, int y);
void free_uf(unionfind* uf);

// BOUNDS
int new_uf_bound(int n);
int find_bound(unionfind* uf, int x);
int merge_bound(unionfind* uf, int x, int y);

#endif

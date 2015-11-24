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

#endif

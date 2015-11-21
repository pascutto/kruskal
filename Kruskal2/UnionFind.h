#ifndef UNIONFIND_H_INCLUDED
#define UNIONFIND_H_INCLUDED

#include <stdlib.h>

typedef struct
{
    size_t size;
    int *parent;
    unsigned int *rank;
} UnionFind;

UnionFind makeSet(size_t size);
void destroyUF(UnionFind uf);

void Union(UnionFind uf, size_t x, size_t y);
size_t Find(UnionFind uf, size_t x);


#endif // UNIONFIND_H_INCLUDED

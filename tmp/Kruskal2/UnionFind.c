#include "UnionFind.h"

UnionFind makeSet(size_t size)
{
    UnionFind uf;
    uf.size = size;
    uf.parent = malloc(sizeof(int)*size);
    uf.rank   = calloc(size, sizeof(int));

    for(size_t i=0; i<size; ++i)
        uf.parent[i] = -1;

    return uf;
}

void destroyUF(UnionFind uf)
{
    free(uf.parent);
}

size_t Find(UnionFind uf, size_t x)
{
    if(uf.parent[x]==-1)
        return x;

    uf.parent[x] = Find(uf, uf.parent[x]);
    return uf.parent[x];
}

void Union(UnionFind uf, size_t x, size_t y)
{
    size_t xr = Find(uf, x);
    size_t yr = Find(uf, y);

    if(xr==yr)
        return;

    if(uf.rank[xr] < uf.rank[yr])
         uf.parent[xr] = yr;
    if(uf.rank[yr] < uf.rank[xr])
         uf.parent[yr] = xr;
    else
    {
        uf.parent[xr] = yr;
        ++uf.rank[xr];
    }
}

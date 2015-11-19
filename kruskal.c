#include "graph.h"
#include "sort.h"
#include "unionfind.h"
#include <stdlib.h>

edge* kruskal_edges(int n, int m, edge* v) {
	unionfind uf;
    uf = new_uf(n);
	sort(v, m);
	edge* ans = malloc((n - 1) * sizeof(edge));
	int pos = 0;
	int i;
	for(i = 0; i < m; i++) 
		if (merge(&uf, v[i].x, v[i].y)) {
			ans[pos] = v[i];
			pos++;
		}
	return ans;
}

edge* kruskal_graph(graph* g) {
	return kruskal_edges(g->n, g->m, edge_array_of_graph(g));
}

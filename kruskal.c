#include "graph.h"
#include "sort.h"
#include "unionfind.h"
#include <stdlib.h>

edge* kruskal_edges(int n, int m, edge* v) {
	int parent[n];
	int rank[n];
	int i;
	for(i = 0; i < n; i++) {
		parent[i] = -1;
		rank[i] = 1;
	}
	sort(v, m);
	edge* ans = malloc((n - 1) * sizeof(edge));
	int pos = 0;
	for(i = 0; i < m; i++) 
		if (merge(parent, rank, v[i].x, v[i].y)) {
			ans[pos] = v[i];
			pos++;
		}
	return ans;
}

edge* kruskal_graph(graph* g) {
	return kruskal_edges(g->n, g->m, edge_array_of_graph(g));
}

#include "graph.h"
#include "error.h"
#include "sort.h"
#include "unionfind.h"
#include <stdlib.h>
#include <stdio.h>

edge* kruskal_edges(int n, int m, edge* v) {
	unionfind uf;
	uf = new_uf(n);
	sort(v, 2 * m);

	edge* ans = NULL;
    ans = malloc((n - 1) * sizeof(edge));
	check_alloc(ans);

    int pos = 0;
	int i;
	for(i = 0; i < 2 * m; i++) 
		if (merge(&uf, v[i].x, v[i].y)) {
			ans[pos] = v[i];
			pos++;
		}
    
    free_uf(&uf);
    return ans;
}   

int kruskal_edges_bound(int n, int m, edge* v) {
    unionfind uf = new_uf(n);
    return new_uf_bound(n) + sort_bound(v, 2 * m) + 2 * m * merge_bound(&uf, 0, 0);
}

edge* kruskal_graph(graph* g) {
    edge* edges = edge_array_of_graph(g);
    edge* ans = kruskal_edges(g->n, g->m, edges);
    free_edges(edges);
    return ans;
}

int kruskal_graph_bound(graph* g) {
    return edge_array_of_graph_bound(g) + kruskal_edges_bound(g->n, g->m, edge_array_of_graph(g));
}

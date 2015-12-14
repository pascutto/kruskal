#ifndef _KRUSKAL_HEADER_
#define _KRUSKAL_HEADER_

edge* kruskal_graph(graph* g);
edge* kruskal_edges(int n, int m, edge* v);

// BOUNDS
int kruskal_edges_bound(int n, int m, edge* v);
int kruskal_graph_bound(graph* g);

#endif

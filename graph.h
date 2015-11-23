#ifndef _GRAPH_HEADER_
#define _GRAPH_HEADER_

// Representing the edge x -> y with weight w.
typedef struct {
	int x;
	int y;
	double w;
} edge;

// Representing an element of a chained adjacency list of a graph.
typedef struct {
    int y;
    double w;
    struct elem* next;
} elem;

typedef elem* list;

// Representing a weighted graph.
typedef struct {
    int n;			// Number of vertices
    int m;			// Number of edges
    list* adj;		// Adjacency list
} graph;

graph* read_from_file(char* fileName);
edge* edge_array_of_graph(graph* g);

#endif

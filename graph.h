#ifndef _GRAPH_HEADER_
#define _GRAPH_HEADER_

typedef struct {
	int x;
	int y;
	double w;
} edge;

struct elem {
    int y;
    double w;
    struct elem* next;
};

typedef struct elem elem;

typedef elem* list;

typedef struct {
    int n;
    int m;
    list* adj;
} graph;

graph* graph_from_file(char* fileName);
edge* edge_array_of_graph(graph* g);

#endif

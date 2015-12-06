#include "kruskal.h"
#include "graph.h"
#include "tsp.h"
#include "error.h"
#include <stdio.h>

int* trading_salesman_problem(graph* g) {
    int* v = NULL;
    v = malloc(g->n * sizeof(int));
    check_alloc(v);

    edge* ans = kruskal_graph(g);
    


    return v;
}

#include "error.h"
#include "graph.h"
#include "kruskal.h"
#include "tsp.h"
#include <stdio.h>
#include <stdlib.h>

void build_road(int* v, int father, int node, edge* edges, int m) {
    ++v[0];
    v[v[0]] = node;

    int i;
    for (i = 0; i < m; ++i)
        if (edges[i].x == node && edges[i].y != father) 
            build_road(v, node, edges[i].y, edges, m);
        else if (edges[i].y == node && edges[i].x != father)
            build_road(v, node, edges[i].x, edges, m);
}

int* travelling_salesman_problem(graph* g) {
    int* v = NULL;
    v = malloc((g->n + 1) * sizeof(int));
    check_alloc(v);

    edge* mst = kruskal_graph(g);
    
    v[0] = 0;
    build_road(v, -1, 0, mst, g->n - 1);
    
    return &v[1];
}

int travelling_salesman_problem_bound(graph* g) {
    return kruskal_graph_bound(g) + g->n;
}

double find_in_list(list l, int val) {
    elem* current = l;
    for (current; current != NULL; current = current->next)
        if (current->y == val)
            return current->w;
    fprintf(stderr, "The graph is not complete.");
    exit(42); //EASTER EGG
}

double cost_travelling_salesman_problem(int* ord, graph* g) {
    double ans = 0;
    
    int i;
    for (i = 1; i < g->n; ++i)
        ans += find_in_list(g->adj[ord[i - 1]], ord[i]);

    ans += find_in_list(g->adj[ord[g->n - 1]], ord[0]);

    return ans;
}

int cost_travelling_salesman_problem_bound(int* ord, graph* g) {
    return g->n * g->n;
    /* 
        Let n be g->n (the number of nodes).
        Taking into account the fact that the graph is complete and that there are no repeated edges, the degree of every node is n - 1.
        Thus, the complexity of find_in_list is, in the worst case, n.
    */       
}

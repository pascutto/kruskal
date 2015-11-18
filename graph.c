#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

graph read_from_file(char* fileName) {
    FILE *fin = fopen(fileName, "r");
    
    int n, m;
    fscanf(fin, "%d%d", &n, &m);
    
    list adj[n];
    int i;
    for (i = 0; i < n; ++i)
        adj[i] = NULL;

    for (i = 0; i < m; ++i) {
        int st, end;
        double w;
        scanf("%d%d%lf", &st, &end, &w);
        
        elem* n1 = malloc(sizeof(elem));
        n1->y = end;
        n1->next = adj[st];
        adj[st] = n1;
        elem* n2 = malloc(sizeof(elem));
        n2->y = st;
        n2->next = adj[end];
        adj[end] = n2;
    }
    
    fclose(fin);

    graph* g = malloc(sizeof(elem));
    g->n = n;
    g->m = m;
    g->adj = adj;

    return *g;
}

edge* edge_list_of_graph(graph* g) {
    edge* v = malloc(g->m * sizeof(edge));
    
    int pc = 0;
    
    int i;
    for (i = 0; i < g->n; ++i) {
        elem* current = g->adj[i];

        for (current; current != NULL; current = current->next)
            if (current->y >= i) {
                edge* e = malloc(sizeof(edge));
                e->x = i;
                e->y = current->y;
                e->w = current->w;
                v[pc] = *e;
                pc++;
            }
                
    }
    
    return v;
}

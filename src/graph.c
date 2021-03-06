#include "graph.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

graph* read_from_file(char* fileName) {
    FILE *fin = NULL;
	fin = fopen(fileName, "r");
	if (fin == NULL) {
		fprintf(stderr, "Erreur de lecture du fichier %s", fileName);
		exit(2);
	}

    int n, m;
    fscanf(fin, "%d%d", &n, &m);
    
    list *adj = NULL;
	adj = malloc(n * sizeof(elem));
    check_alloc(adj);
	
	int i;
    for (i = 0; i < n; ++i)
        adj[i] = NULL;
    
    for (i = 0; i < m; ++i) {
        int st, end;
        double w;
        fscanf(fin, "%d%d%lf", &st, &end, &w);
        
        elem* n1 = NULL;
		n1 = malloc(sizeof(elem));
		check_alloc(n1);

        n1->y = end;
        n1->w = w;
        n1->next = adj[st];
        adj[st] = n1;

        elem* n2 = NULL;
		n2 = malloc(sizeof(elem));
		check_alloc(n2);
        
		n2->y = st;
        n2->w = w;
        n2->next = adj[end];
        adj[end] = n2;
    }
    
    fclose(fin);

    graph* g = NULL;
    g =	malloc(sizeof(graph));
	check_alloc(g);

    g->n = n;
    g->m = m;
    g->adj = adj;

    return g;
}

edge* edge_array_of_graph(graph* g) {
    edge* v = NULL;
    v =	malloc(g->m * 2 * sizeof(edge));
	check_alloc(v);
    
    int pc = 0;
    
    int i;
    for (i = 0; i < g->n; ++i) {
        elem* current = g->adj[i];

        for (current; current != NULL; current = current->next) {
            edge* e = NULL;
			e = malloc(sizeof(edge));
			check_alloc(e);

            e->x = i;
            e->y = current->y;
            e->w = current->w;
            v[pc] = *e;
            pc++;
        }
    }
    
    return v;
}

int edge_array_of_graph_bound(graph* g) {
    return g->m + g->n;
}

void free_list(list l) {
    while (l != NULL) {
        list aux = l -> next;
        free(l);
        l = aux;
    }
}

void free_graph(graph* g) {
    int i;
    for (i = 0; i < g->n; ++i)
        free_list(g->adj[i]);
    free(g->adj);
    free(g);
}

void free_edges(edge* ed) {
    free(ed);
}

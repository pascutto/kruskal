#include "graph.h"
#include "kruskal.h"
#include "tsp.h"
#include <stdio.h>

int main_bound(int job, graph* g) {
    if (job == 0) 
        return kruskal_graph_bound(g) + g->n;
    return travelling_salesman_problem_bound(g) + cost_travelling_salesman_problem_bound(travelling_salesman_problem(g), g);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Missing argument. Expected format: job in_file out_file. (job should be 0 for Kruskal or 1 for Trading Salesman)\n");
        return 0;
    }

    graph* g = read_from_file(argv[2]);
    FILE *f = fopen(argv[3], "w");

    if (atoi(argv[1]) == 0) {
        edge* edg = kruskal_graph(g);
    
        int i;
        double ans = 0;
        for (i = 0; i < g->n - 1; ++i)
            ans += edg[i].w;
    
        fprintf(f, "%lf\n", ans);
        fprintf(f, "%d\n", g->n - 1);
        for (i = 0; i < g->n - 1; ++i)
            fprintf(f, "%d %d %lf\n", edg[i].x, edg[i].y, edg[i].w);
    
        free_edges(edg);
    } else if (atoi(argv[1]) == 1) {        
        int* order = travelling_salesman_problem(g);
        double ans = cost_travelling_salesman_problem(order, g);
        
        int i;
        for (i = 0; i < g->n; ++i)
            fprintf(f, "%d ", order[i]);
        fprintf(f, "%d\n", order[0]);

        fprintf(f, "%lf\n", ans);
    } else {
        printf("Illegal job id.");
        return 0;
    }

    free_graph(g);
    fclose(f);

    return 0;
}

#include "graph.h"
#include "kruskal.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Missing argument. Expected format: in_file out_file job. (job should be 0 for Kruskal or 1 for Trading Salesman)\n");
        return 0;
    }

    graph* g = read_from_file(argv[1]);
    FILE *f = fopen(argv[2], "w");

    if (atoi(argv[3]) == 0) {
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
    } else {
    }

    free_graph(g);
    fclose(f);

    return 0;
}

#include "graph.h"
#include "kruskal.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Missing argument. Expected format: in_file out_file\n");
        return 0;
    }
    graph* g = read_from_file(argv[1]);
    
    edge* edg = kruskal_graph(g);
    
    int i;
    double ans = 0;
    for (i = 0; i < g->n - 1; ++i)
        ans += edg[i].w;
    
    FILE *f = fopen(argv[2], "w");

    fprintf(f, "%lf\n", ans);
    fprintf(f, "%d\n", g->n - 1);
    for (i = 0; i < g->n - 1; ++i)
        fprintf(f, "%d %d %lf\n", edg[i].x, edg[i].y, edg[i].w);
    
    free_edges(edg);
    free_graph(g);

    return 0;
}

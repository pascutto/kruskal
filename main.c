#include "graph.h"
#include "kruskal.h"
#include <stdio.h>

int main() {
    char ch[100];
    printf("Input file:\n");
    scanf("%s", ch);
    graph* g = read_from_file(ch);
    
    edge* edg = kruskal_graph(g);
    
    int i;
    double ans = 0;
    for (i = 0; i < g->n - 1; ++i)
        ans += edg[i].w;
    printf("%lf\n", ans);

    /*for (i = 0; i < g->n - 1; ++i)
        printf("%d %d %lf\n", edg[i].x, edg[i].y, edg[i].w);*/
    
    // TODO : fix warning
    // TODO : fix sigsegv on pretests/grader_test6.in
    // TODO : memory deallocation
    // TODO : malloc verification

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "randFunc.h"
#include "error.h"

///adjacency list for a node
typedef struct {
    int x, y;
    double w;
} edge;

///represents a graph by adjacency lists
typedef struct {
    int n, m;
    edge *edges;
} graph;

///create a random graph
graph createGraph(int n, int m, double minWeight, double maxWeight) {
    graph graph; 

    graph.n = n;
    graph.m = 0;
    
    int i;

    //allocate the memory for the adjacency lists
    graph.edges = malloc(sizeof(edge) * m);
    if (graph.edges == NULL)
        error("Impossible d'allouer le graphe");
    
    // force the graph to be connex  
    int *ord = randomPermutation(n);

    for (i = 1; i < n; ++i) {
        graph.edges[graph.m].x = ord[i];
        graph.edges[graph.m].y = ord[uniformDistributionInt(0, i)];
        graph.edges[graph.m].w = uniformDistributionDouble(minWeight, maxWeight);
        graph.m++; 
    }

    for (i = graph.m; i < m; ++i) {
        int ec = uniformDistributionInt(0, n * n);
        graph.edges[graph.m].x = ec % n;
        graph.edges[graph.m].y = ec / n;
        graph.edges[graph.m].w = uniformDistributionDouble(minWeight, maxWeight);
        graph.m++;
    }
    
    graph.m = m;

    return graph;
}

///free the memory of the graph
void destroyGraph(graph graph) {
    free(graph.edges);
}


///format the graph to the requested format and print it
void printGraph(graph graph, char *output) {   
    FILE *f = fopen(output, "w");
    fprintf(f, "%d %d\n", graph.n, graph.m);
    
    int i;
    for (i = 0; i < graph.m; ++i)
        fprintf(f, "%d %d %lf\n", graph.edges[i].x, graph.edges[i].y, graph.edges[i].w);

    fclose(f);
}

///format a graph for graphviz
void printDot(graph g, int w) {
    printf("graph g {\n");
    printf("node [color=blue4 fillcolor=azure1 style=filled fontsize=16 fontcolor=blue3]\n");
    printf("edge [color=darkgreen, fontcolor=red4]\n");

    int i;
    for (i = 0; i < g.m; ++i)
        if (w) 
            printf("%d--%d [label=%lf]\n", g.edges[i].x, g.edges[i].y, g.edges[i].w);
        else
            printf("%d- -%d\n", g.edges[i].x, g.edges[i].y);

    printf("}\n");
}

int main(int argc, char **argv) {
    if(argc != 6) {
        printf("Usage: graphgen nbVertice nbEdges minWeight maxWeight outputName\n");
    } else {
        srand(time(NULL));
        graph graph = createGraph(atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atof(argv[4]));

        printGraph(graph, argv[5]);
        //printDot(graph, 1);

        destroyGraph(graph);
    }

    return 0;
}

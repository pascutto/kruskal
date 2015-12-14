#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "randFunc.h"
#include "error.h"

//adjacency list for a node
typedef struct {
    int x, y;
    double w;
} edge;

// represents a graph by adjacency lists
typedef struct {
    int n, m;
    edge *edges;
} graph;

typedef struct {
    double x, y;
} point;

// create a random graph
graph createGraph(int n, int m, double minWeight, double maxWeight) {
    graph graph; 

    graph.n = n;
    graph.m = 0;
    
    int i;

    // allocate the memory for the adjacency lists
    graph.edges = malloc(sizeof(edge) * m);
    if (graph.edges == NULL)
        error("Impossible d'allouer le graphe.");
    
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

point* generatePoints(int n) {
    point *p = malloc(n * sizeof(point));
    if (p == NULL)
        error("Impossible d'allouer le vecteur de points.");

    int i;
    for (i = 0; i < n; ++i) {
        p[i].x = uniformDistributionDouble(0., 1000.);
        p[i].y = uniformDistributionDouble(0., 1000.);
    }

    return p;
}

// free the memory of the graph
void destroyGraph(graph *graph) {
    free(graph->edges);
}

void destroyPoints(point *points) {
    free(points);
}

// format the graph to the requested format and print it
void printGraph(graph *graph, char *output) {   
    FILE *f = fopen(output, "w");
    fprintf(f, "%d %d\n", graph->n, graph->m);
    
    int i;
    for (i = 0; i < graph->m; ++i)
        fprintf(f, "%d %d %lf\n", graph->edges[i].x, graph->edges[i].y, graph->edges[i].w);

    fclose(f);
}

double euclideanDistance(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void printGraphOfPoints(point *points, int n, char *output) {
    FILE *f = fopen(output, "w");
    fprintf(f, "%d %d\n", n, n * (n - 1) / 2);

    int i, j;
    for (i = 0; i < n; ++i)
        for (j = i + 1; j < n; ++j)
            fprintf(f, "%d %d %lf\n", i, j, euclideanDistance(points[i], points[j]));

    fclose(f);
}

// dotty printing
void printDot(graph *g, int w) {
    printf("graph g {\n");
    printf("node [color=blue4 fillcolor=azure1 style=filled fontsize=16 fontcolor=blue3]\n");
    printf("edge [color=darkgreen, fontcolor=red4]\n");

    int i;
    for (i = 0; i < g->m; ++i)
        if (w) 
            printf("%d--%d [label=%lf]\n", g->edges[i].x, g->edges[i].y, g->edges[i].w);
        else
            printf("%d- -%d\n", g->edges[i].x, g->edges[i].y);

    printf("}\n");
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    if (argc < 2) {
        printf("Mandatory parameter is missing. 0 - Generate Kruskal testcase; 1 - Generate Trading Salesman testcase.\n");
    } else if (atoi(argv[1]) == 0) {
        if (argc != 7)
            printf("Usage: 0 nbNodes nbEdges minWeight maxWeight outputName.\n");
        else {
            graph graph = createGraph(atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]));

            printGraph(&graph, argv[6]);
            //printDot(&graph, 1);

            destroyGraph(&graph);
        }
    } else if (atoi(argv[1]) == 1) {
        if (argc != 4)
            printf("Usage: 1 nbNodes outputName.\n");
        else {
            point *points = generatePoints(atoi(argv[2]));

            printGraphOfPoints(points, atoi(argv[2]), argv[3]);

            destroyPoints(points);
        }
    } else {
        printf("Illegal job id.\n");
        return 0;
    }

    return 0;
}

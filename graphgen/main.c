#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "randFunc.h"
#include "error.h"

///adjacency list for a node
typedef struct
{
    int x, y;
    double w;
} edge;

///represents a graph by adjacency lists
typedef struct
{
    int n, m;
    edge *edges;
} graph;

///return whether or not the edge e is already present in the array tab
int find(edge e, edge *tab, int m)
{
    int i;
    for(i=0; i<m; ++i)
    {
        if((e.x==tab[i].x && e.y==tab[i].y) || (e.x==tab[i].y && e.y==tab[i].x))
            return 1;
    }
    return 0;
}


///create a random graph
graph createGraph(int n, int m, double minWeight, double maxWeight)
{
    graph graph;

    graph.n = n;
    graph.m = 0;
    
    int i;

    //allocate the memory for the adjacency lists
    graph.edges = malloc(sizeof(edge)*m);
    if(graph.edges==NULL)
        error("Impossible d'allouer le graphe");

    //sparse graphs
    if(m<n*sqrt(n))
    {
        //for each edge, generate it randomly, then verify there are no collisions with the previous ones: if there are, choose another edge and restart
        for(i=0; i<m; ++i)
        {
            edge e;
            do
            {
                e.x = uniformDistribInt(0, n - 1);
                e.y = uniformDistribInt(0, n - 1);
            }while(find(e, graph.edges, graph.m));

            e.w = uniformDistribDouble(minWeight, maxWeight);

            graph.edges[graph.m] = e;
             ++graph.m;
        }
    }
    else //dense graphs
    {
        //generate an array of nbE distinct edges, and add them to graph
        int* tab = distinctRandomNumbers(0, n*n, m);

        for(i=0; i<m; ++i)
        {
            graph.edges[i].x = tab[i]%n;
            graph.edges[i].y = tab[i]/n;
            graph.edges[i].w = uniformDistribDouble(minWeight, maxWeight);
        }
        graph.m = m;

        free(tab);
    }

    return graph;
}

///free the memory of the graph
void destroyGraph(graph graph)
{
    free(graph.edges);
}


///format the graph to the requested format and print it
void printGraph(graph graph)
{
    printf("%d %d\n", graph.n, graph.m);
    int i;
    for(i=0; i<graph.m; ++i)
    {
        printf("%d %d %lf\n", graph.edges[i].x, graph.edges[i].y, graph.edges[i].w);
    }
}

///format a graph for graphviz
void printDot(graph g, int w)
{
    printf("graph g {\n");
    printf("node [color=blue4 fillcolor=azure1 style=filled fontsize=16 fontcolor=blue3]\n");
    printf("edge [color=darkgreen, fontcolor=red4]\n");

    int i;
    for(i=0; i<g.m; ++i)
    {
        if(w) printf("%d--%d [label=%lf]\n", g.edges[i].x, g.edges[i].y, g.edges[i].w);
        else  printf("%d--%d\n", g.edges[i].x, g.edges[i].y);
    }

    printf("}\n");
}

int main(int argc, char **argv)
{
    if(argc!=5)
    {
        printf("Usage: graphgen nbVertice nbEdges minWeight maxWeight\n");
    }
    else
    {
        srand(time(NULL));
        graph graph = createGraph(atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atof(argv[4]));

        printGraph(graph);
        //printDot(graph, 1);

        destroyGraph(graph);
    }
    return 0;
}

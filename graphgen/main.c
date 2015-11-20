#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "randFunc.h"
#include "error.h"

typedef size_t id;

///adjacency list for a node
typedef struct
{
    id s,t;
    unsigned int weight;
}Edge;

///represents a graph by adjacency lists
typedef struct
{
    id nbVertice, nbEdges;
    Edge *edges;
}Graph;

///return whether or not the edge e is already present in the array tab
int find(Edge e, Edge *tab, id nbE)
{
    for(id i=0; i<nbE; ++i)
    {
        if((e.s==tab[i].s && e.t==tab[i].t) || (e.s==tab[i].t && e.t==tab[i].s))
            return 1;
    }
    return 0;
}


///create a random graph
Graph createGraph(id nbV, id nbE, unsigned int meanWeight, unsigned int maxWeight)
{
    Graph graph;

    graph.nbVertice = nbV;
    graph.nbEdges = 0;

    //allocate the memory for the adjacency lists
    graph.edges = malloc(sizeof(Edge)*nbE);
    if(graph.edges==NULL)
        error("Impossible d'allouer le graphe");

    //sparse graphs
    if(nbE<nbV*sqrt(nbV))
    {
        //for each edge, generate it randomly, then verify there are no collisions with the previous ones: if there are, choose another edge and restart
        for(id i=0; i<nbE; ++i)
        {
            Edge e;
            do
            {
                e.s = uniformDistrib(0, nbV);
                e.t = uniformDistrib(0, nbV);
            }while(find(e, graph.edges, graph.nbEdges));

            e.weight = binomialDistrib(maxWeight, (double)meanWeight/maxWeight);

            graph.edges[graph.nbEdges] = e;
            ++graph.nbEdges;
        }
    }
    else //dense graphs
    {
        //generate an array of nbE distinct edges, and add them to graph
        id* tab = distinctRandomNumbers(0, nbV*nbV, nbE);

        for(id i=0; i<nbE; ++i)
        {
            graph.edges[i].s = tab[i]%nbV;
            graph.edges[i].t = tab[i]/nbV;
            graph.edges[i].weight = binomialDistrib(maxWeight, (double)meanWeight/maxWeight);
        }
        graph.nbEdges = nbE;

        free(tab);
    }

    return graph;
}

///free the memory of the graph
void destroyGraph(Graph graph)
{
    free(graph.edges);
}


///format the graph to the requested format and print it
void printGraph(Graph graph)
{
    printf("%i %i\n", graph.nbVertice, graph.nbEdges);
    for(id i=0; i<graph.nbEdges; ++i)
    {
        printf("%u %u %u\n", graph.edges[i].s, graph.edges[i].t, graph.edges[i].weight);
    }
}

///format a graph for graphviz
void printDot(Graph g, int w)
{
    printf("graph g {\n");
    printf("node [color=blue4 fillcolor=azure1 style=filled fontsize=16 fontcolor=blue3]\n");
    printf("edge [color=darkgreen, fontcolor=red4]\n");

    for(size_t i=0; i<g.nbEdges; ++i)
    {
        if(w) printf("%u--%u [label=%u]\n", g.edges[i].s, g.edges[i].t, g.edges[i].weight);
        else  printf("%u--%u\n", g.edges[i].s, g.edges[i].t);
    }

    printf("}\n");
}

int main(int argc, char **argv)
{
    if(argc!=5)
    {
        printf("Usage: graphgen nbVertice nbEdges meanWeight maxWeight\n");
    }
    else
    {
        Graph graph = createGraph(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

        printGraph(graph);
        //printDot(graph, 1);

        destroyGraph(graph);
    }
    return 0;
}

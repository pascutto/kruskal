#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "UnionFind.h"


///adjacency list for a node
typedef struct
{
    size_t s,t;
    unsigned int weight;
}Edge;

///represents a graph by adjacency lists
typedef struct
{
    size_t nbVertice, nbEdges;
    Edge *edges;
}Graph;


/////////////////////////////////////////////////////////
//Sort

int lower(Edge a, Edge b)
{
    return a.weight<b.weight;
}

size_t pivot(Edge *tab, size_t p, size_t r)
{
    Edge pivot = tab[p];
    size_t i = p-1, j = r+1;
    Edge temp;
    while (1)
    {
        do j--;
        while (lower(pivot, tab[j]));

        do i++;
        while (lower(tab[i], pivot));

        if (i<j)
        {
            temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
        else
            return j;
    }
}

void quickSort(Edge *tab, size_t p, size_t r)
{
    size_t q;
    if (p < r)
    {
        q = pivot(tab, p, r);
        quickSort(tab, p, q);
        quickSort(tab, q+1, r);
    }
}

/////////////////////////////////////////////////////////


///free the memory of the graph
void destroyGraph(Graph graph)
{
    free(graph.edges);
}

Graph loadGraph(char *filename)
{
    FILE *f = fopen(filename, "r");
    if(f==NULL)
        error("Impossible de lire le fichier");

    Graph graph;

    fscanf(f, "%d %d", &graph.nbVertice, &graph.nbEdges);

    graph.edges = malloc(sizeof(Edge)*graph.nbEdges);
    if(graph.edges==NULL)
        error("Impossible d'allouer les noeuds");

    for(size_t i=0; i<graph.nbEdges; ++i)
    {
        unsigned int a,b,c;
        fscanf(f, "%u %u %u", &a, &b, &c);
        graph.edges[i].s = a;
        graph.edges[i].t = b;
        graph.edges[i].weight = c;
    }

    fclose(f);

    return graph;
}


Graph kruskal(Graph g)
{
    UnionFind uf = makeSet(g.nbVertice);

    Graph tree;
    tree.nbVertice = g.nbVertice;
    tree.edges = malloc(sizeof(Edge)*g.nbEdges);
    tree.nbEdges = 0;

    quickSort(g.edges, 0, g.nbEdges-1);

    for(size_t i=0; i<g.nbEdges; ++i)
    {
        if(Find(uf, g.edges[i].s) != Find(uf, g.edges[i].t))
        {
            tree.edges[tree.nbEdges] = g.edges[i];
            ++tree.nbEdges;
            Union(uf, g.edges[i].s, g.edges[i].t);
        }
    }
    return tree;
}

void printDot(Graph g, char *col, int poids)
{
    printf("subgraph g {\n");
    printf("node [color=blue4 fillcolor=azure1 style=filled fontsize=16 fontcolor=blue3]\n");
    printf("edge [color=darkgreen, fontcolor=red4]\n");
    for(size_t i=0; i<g.nbEdges; ++i)
    {
        if(poids) printf("%u--%u [label=%u, len=%u, color=%s]\n", g.edges[i].s, g.edges[i].t, g.edges[i].weight, g.edges[i].weight, col);
        else      printf("%u--%u [len=%u, color=%s]\n", g.edges[i].s, g.edges[i].t, g.edges[i].weight, col);
    }
    printf("}\n");
}

int findE(Edge e, Edge *tab, size_t nbE)
{
    for(size_t i=0; i<nbE; ++i)
    {
        if(e.s==tab[i].s && e.t==tab[i].t)
            return i;
    }
    return -1;
}

Graph delta(Graph g, Graph h)
{
    for(size_t i=0; i<h.nbEdges; ++i)
    {
        int a = findE(h.edges[i], g.edges, g.nbEdges);
        if(a!=-1)
        {
            g.edges[a] = g.edges[g.nbEdges-1];
            --g.nbEdges;
        }
    }
    return g;
}

int main(int argc, char **argv)
{
    if(argc!=2)
        error("Usage: Kruskal filename");

    Graph g = loadGraph(argv[1]);
    Graph tree = kruskal(g);

    printf("graph g {\n");
    printDot(tree, "red2", 1);
    printDot(delta(g, tree), "darkgreen", 1);
    printf("}");

    destroyGraph(g);
    destroyGraph(tree);

    return 0;
}

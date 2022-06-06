#include <stdio.h>
#include <stdlib.h>
#include "Graphs.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Graphs.h" // 'INTERFACES'

typedef struct graphs Graphs;

Graphs* createGraph(int numberOfVertices, int maxDegree, int isWeighted);

int insertsEdge(Graphs* graphs, int origin, int dest, int isDigraph, float peso);

void Dijkstra(Graphs *graph,  int origin, int destiny);


struct graphs
{
    int isWeighted;
    int numberOfVertices;
    int maxDegree;
    int **edges;
    float **weights;
    int *degree;
};

Graphs *createGraph(int numberOfVertices, int maxDegree, int isWeighted)
{
    Graphs *graphs;
    graphs = (Graphs *)malloc(sizeof(struct graphs));
    if (graphs != NULL)
    {
        int i;
        graphs->numberOfVertices = numberOfVertices;
        graphs->maxDegree = maxDegree;
        graphs->isWeighted = (isWeighted != 0) ? 1 : 0;
        graphs->degree = (int *)calloc(numberOfVertices, sizeof(int));

        graphs->edges = (int **)malloc(numberOfVertices * sizeof(int *));
        for (i = 0; i < numberOfVertices; i++)
            graphs->edges[i] = (int *)malloc(maxDegree * sizeof(int));

        if (graphs->isWeighted)
        {
            graphs->weights = (float **)malloc(numberOfVertices * sizeof(float *));
            for (i = 0; i < numberOfVertices; i++)
                graphs->weights[i] = (float *)malloc(maxDegree * sizeof(float));
        }
    }
    return graphs;
}

int insertsEdge(Graphs *graphs, int origin, int dest, int isDigraph, float peso)
{
    if (graphs == NULL)
        return 0;
    if (origin < 0 || origin >= graphs->numberOfVertices)
        return 0;
    if (dest < 0 || dest >= graphs->numberOfVertices)
        return 0;

    graphs->edges[origin][graphs->degree[origin]] = dest;
    if (graphs->isWeighted)
        graphs->weights[origin][graphs->degree[origin]] = peso;
    graphs->degree[origin]++;

    if (isDigraph == 0)
        insertsEdge(graphs, dest, origin, 1, peso);
    return 1;
}

void Dijkstra(Graphs *graph,  int origin, int destiny)
{
    int i, v, cont = 0;
    int *ant, *tmp;
    int *findedShortPath; 
    double minValue;
    double dist[graph->numberOfVertices];
    ant = (int *)calloc(graph->numberOfVertices, sizeof(int *));
    if (ant == NULL)
    {
        system("color fc");
        printf("** Erro: Memoria Insuficiente **");
        exit(-1);
    }
    tmp = (int *)calloc(graph->numberOfVertices, sizeof(int *));
    if (tmp == NULL)
    {
        system("color fc");
        printf("** Erro: Memoria Insuficiente **");
        exit(-1);
    }
    findedShortPath = (int *)calloc(graph->numberOfVertices, sizeof(int *));
    if (findedShortPath == NULL)
    {
        system("color fc");
        printf("** Erro: Memoria Insuficiente **");
        exit(-1);
    }
    for (i = 0; i < graph->numberOfVertices; i++)
    {
        if (graph->weights[(origin - 1) * graph->numberOfVertices + i] != -1)
        {
            ant[i] = origin - 1;
            dist[i] = graph->weights[(origin - 1) * graph->numberOfVertices + i];
        }
        else
        {
            ant[i] = -1;
            dist[i] = HUGE_VAL;
        }
        findedShortPath[i] = 0;
    }
    findedShortPath[origin - 1] = 1;
    dist[origin - 1] = 0;
    /* Laco principal */
    do
    {
        minValue = HUGE_VAL;
        for (i = 0; i < graph->numberOfVertices; i++)
        {
            if (!findedShortPath[i])
            {
                if (dist[i] >= 0 && dist[i] < minValue)
                {
                    minValue = dist[i];
                    v = i;
                }
            }
        }
        if (minValue != HUGE_VAL && v != destiny - 1)
        {
            findedShortPath[v] = 1;
            for (i = 0; i < graph->numberOfVertices; i++)
            {
                if (!findedShortPath[i])
                {
                    if (graph->weights[v * graph->numberOfVertices + i] != -1 && dist[v] + graph->weights[v * graph->numberOfVertices + i] < dist[i])
                    {
                        dist[i] = dist[v] + graph->weights[v * graph->numberOfVertices + i];
                        ant[i] = v;
                    }
                }
            }
        }
    } while (v != destiny - 1 && minValue != HUGE_VAL);
    printf("\tDe %d para %d: \t", origin, destiny);
    if (minValue == HUGE_VAL)
    {
        printf("Nao Existe\n");
        printf("\tCusto: \t- \n");
    }
    else
    {
        i = destiny;
        i = ant[i - 1];
        while (i != -1)
        {
            tmp[cont] = i + 1;
            cont++;
            i = ant[i];
        }
        for (i = cont; i > 0; i--)
        {
            printf("%d -> ", tmp[i - 1]);
        }
        printf("%d", destiny);
        printf("\n\tCusto: %d\n", (int)dist[destiny - 1]);
    }
}



int main(){

    int isDigraph = 0; // No
    Graphs* graph = createGraph(7, 500, 0);

    insertsEdge(graph, 0, 5, isDigraph, 100);
    insertsEdge(graph, 0, 3, isDigraph, 700);

    insertsEdge(graph, 1, 3, isDigraph, 250);
    insertsEdge(graph, 1, 2, isDigraph, 200);

    insertsEdge(graph, 3, 4, isDigraph, 250);
    insertsEdge(graph, 3, 2, isDigraph, 300);
    insertsEdge(graph, 5, 3, isDigraph, 450);

    insertsEdge(graph, 6, 5, isDigraph, 300);

    int i, father[7];
    Dijkstra(graph, 0, 5);
    for(i = 0; i < 7; i++){
        printf("%d: %d\n", father[i], i);
     }
    printf("\n");
    system("pause");
    return 0;
}

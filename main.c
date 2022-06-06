#include <stdio.h>
#include <stdlib.h>
#include "Graphs.h"


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

typedef struct graphs Graphs;

Graphs* createGraph(int numberOfVertices, int maxDegree, int isWeighted);

int insertsEdge(Graphs* graphs, int origin, int dest, int isDigraph, float peso);

void Dijkstra(Graphs *graph,  int origin, int destiny);

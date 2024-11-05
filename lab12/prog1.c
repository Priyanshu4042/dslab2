#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10 


struct Graph {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};


struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;


    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0; 
        }
    }
    return graph;
}


void addDirectedEdge(struct Graph* graph, int src, int dest) {
    if (src < graph->numVertices && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 1; 
    }
}


void addUndirectedEdge(struct Graph* graph, int src, int dest) {
    if (src < graph->numVertices && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 1; 
        graph->adjMatrix[dest][src] = 1; 
    }
}


void displayGraph(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int vertices;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    struct Graph* directedGraph = createGraph(vertices);
    struct Graph* undirectedGraph = createGraph(vertices);


    addDirectedEdge(directedGraph, 0, 1);
    addDirectedEdge(directedGraph, 0, 2);
    addDirectedEdge(directedGraph, 1, 2);
    addDirectedEdge(directedGraph, 2, 0);
    addDirectedEdge(directedGraph, 2, 3);

    printf("\nDirected Graph:\n");
    displayGraph(directedGraph);


    addUndirectedEdge(undirectedGraph, 0, 1);
    addUndirectedEdge(undirectedGraph, 0, 2);
    addUndirectedEdge(undirectedGraph, 1, 2);
    addUndirectedEdge(undirectedGraph, 1, 3);

    printf("\nUndirected Graph:\n");
    displayGraph(undirectedGraph);

    free(directedGraph);
    free(undirectedGraph);

    return 0;
}
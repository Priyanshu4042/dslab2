#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};


struct Graph {
    int numVertices;
    struct Node** adjLists; 
};


struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}


struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));

    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}


void addDirectedEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode; 
}


void addUndirectedEdge(struct Graph* graph, int src, int dest) {
    
    struct Node* newNode1 = createNode(dest);
    newNode1->next = graph->adjLists[src];
    graph->adjLists[src] = newNode1;

  
    struct Node* newNode2 = createNode(src);
    newNode2->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode2;
}


void displayGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("\nVertex %d:", v);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
    }
    printf("\n");
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


    return 0;
}
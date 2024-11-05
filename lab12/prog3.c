#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100 

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


void addEdge(struct Graph* graph, int src, int dest) {
   
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

   
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}


void bfs(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false}; 
    struct Node* queue[MAX_VERTICES]; 
    int front = 0, rear = 0; 

   
    visited[startVertex] = true;
    queue[rear++] = createNode(startVertex);

    printf("BFS starting from vertex %d:\n", startVertex);

    while (front < rear) {
        
        struct Node* currentNode = queue[front++];
        printf("%d ", currentNode->vertex);

        
        struct Node* temp = graph->adjLists[currentNode->vertex];
        while (temp) {
            int adjVertex = temp->vertex;

           
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = createNode(adjVertex);
            }
            temp = temp->next;
        }
        free(currentNode); 
    }
    printf("\n");
}


int main() {
    int vertices, edges;
    int src, dest;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

   
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (source destination): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startVertex;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);

    bfs(graph, startVertex);



    return 0;
}
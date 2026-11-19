/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 16: Graph Representation using Adjacency Matrix and Adjacency List
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

// Node structure for Adjacency List
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
} AdjListNode;

// Graph structure
typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    AdjListNode *adjList[MAX_VERTICES];
} Graph;

Graph* createGraph(int vertices) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        g->adjList[i] = NULL;
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
    return g;
}

void addEdge(Graph *g, int src, int dest, int weight, int isDirected) {
    // 1. Update Adjacency Matrix
    g->adjMatrix[src][dest] = weight;
    if (!isDirected) {
        g->adjMatrix[dest][src] = weight;
    }

    // 2. Update Adjacency List (add to src)
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;

    // If undirected, add to dest as well
    if (!isDirected) {
        newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        newNode->dest = src;
        newNode->weight = weight;
        newNode->next = g->adjList[dest];
        g->adjList[dest] = newNode;
    }
}

void printAdjacencyMatrix(Graph *g) {
    printf("\n--- Adjacency Matrix ---\n    ");
    for (int i = 0; i < g->numVertices; i++) {
        printf(" V%d ", i);
    }
    printf("\n");

    for (int i = 0; i < g->numVertices; i++) {
        printf("V%d: ", i);
        for (int j = 0; j < g->numVertices; j++) {
            printf(" %2d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void printAdjacencyList(Graph *g) {
    printf("\n--- Adjacency List ---\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vertex %d: ", i);
        AdjListNode *curr = g->adjList[i];
        while (curr != NULL) {
            printf("-> (dest: %d, wt: %d) ", curr->dest, curr->weight);
            curr = curr->next;
        }
        printf("-> NULL\n");
    }
}

void freeGraph(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        AdjListNode *curr = g->adjList[i];
        while (curr != NULL) {
            AdjListNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g);
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 16: Graph Representation (Matrix & List)\n");
    printf("=================================================================\n");

    int V = 5;
    Graph *g = createGraph(V);

    // Adding undirected edges: (src, dest, weight, isDirected)
    addEdge(g, 0, 1, 4, 0);
    addEdge(g, 0, 2, 2, 0);
    addEdge(g, 1, 2, 1, 0);
    addEdge(g, 1, 3, 5, 0);
    addEdge(g, 2, 3, 8, 0);
    addEdge(g, 3, 4, 6, 0);

    printAdjacencyMatrix(g);
    printAdjacencyList(g);

    freeGraph(g);
    return 0;
}

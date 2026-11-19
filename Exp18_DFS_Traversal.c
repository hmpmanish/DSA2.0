/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 18: Depth First Search (DFS) Traversal of a Graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20

void DFSRecursive(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSRecursive(adjMatrix, numVertices, i, visited);
        }
    }
}

void DFS(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSRecursive(adjMatrix, numVertices, startVertex, visited);
    printf("\n");
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 18: Depth First Search (DFS) Traversal\n");
    printf("=================================================================\n");

    int V = 6;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    // Graph Edges:
    // 0 - 1, 0 - 2, 1 - 3, 1 - 4, 2 - 4, 3 - 5, 4 - 5
    int edges[][2] = {
        {0, 1}, {0, 2},
        {1, 3}, {1, 4},
        {2, 4},
        {3, 5}, {4, 5}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    for (int i = 0; i < numEdges; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    DFS(adjMatrix, V, 0);
    DFS(adjMatrix, V, 3);

    return 0;
}

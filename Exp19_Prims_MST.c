/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 19: Minimum Spanning Tree (MST) using Prim's Algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define V 5

int findMinKeyVertex(int key[], bool mstSet[]) {
    int min = INT_MAX, minIndex = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printMST(int parent[], int graph[V][V]) {
    int totalCost = 0;
    printf("\nEdges in Minimum Spanning Tree (Prim's Algorithm):\n");
    printf("   Edge   | Weight\n");
    printf("----------+-------\n");
    for (int i = 1; i < V; i++) {
        printf("  %d - %d   |   %2d\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    printf("------------------\n");
    printf("Total Cost of Minimum Spanning Tree: %d\n", totalCost);
}

void primMST(int graph[V][V]) {
    int parent[V];  // Array to store constructed MST
    int key[V];     // Key values used to pick minimum weight edge
    bool mstSet[V]; // To represent set of vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first vertex in MST
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < V - 1; count++) {
        int u = findMinKeyVertex(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            // graph[u][v] is non zero only for adjacent vertices
            // mstSet[v] is false for vertices not yet included in MST
            // Update key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 19: Prim's Algorithm for Minimum Spanning Tree\n");
    printf("=================================================================\n");

    /*
           2       3
       (0)---(1)---(2)
        |    / \    |
       6|  8/   \5  |7
        |  /     \  |
       (3)---------(4)
              9
    */
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(graph);

    return 0;
}

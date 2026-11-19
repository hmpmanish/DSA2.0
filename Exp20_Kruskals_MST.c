/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 20: Minimum Spanning Tree (MST) using Kruskal's Algorithm
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Subset {
    int parent;
    int rank;
} Subset;

// Find set of an element i (with path compression)
int findRoot(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = findRoot(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union of two sets by rank
void unionSubsets(Subset subsets[], int x, int y) {
    int xroot = findRoot(subsets, x);
    int yroot = findRoot(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparator function for qsort
int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight - e2->weight;
}

void kruskalMST(int V, int E, Edge edges[]) {
    // 1. Sort all edges in non-decreasing order of weight
    qsort(edges, E, sizeof(Edge), compareEdges);

    // Allocate memory for V subsets
    Subset *subsets = (Subset *)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge *result = (Edge *)malloc((V - 1) * sizeof(Edge));
    int edgeCount = 0; // Number of edges included in MST
    int i = 0;         // Initial index of sorted edges

    while (edgeCount < V - 1 && i < E) {
        Edge nextEdge = edges[i++];

        int x = findRoot(subsets, nextEdge.src);
        int y = findRoot(subsets, nextEdge.dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            result[edgeCount++] = nextEdge;
            unionSubsets(subsets, x, y);
        }
    }

    // Print MST
    int totalCost = 0;
    printf("\nEdges in Minimum Spanning Tree (Kruskal's Algorithm):\n");
    printf("   Edge   | Weight\n");
    printf("----------+-------\n");
    for (i = 0; i < edgeCount; i++) {
        printf("  %d - %d   |   %2d\n", result[i].src, result[i].dest, result[i].weight);
        totalCost += result[i].weight;
    }
    printf("------------------\n");
    printf("Total Cost of Minimum Spanning Tree: %d\n", totalCost);

    free(subsets);
    free(result);
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 20: Kruskal's Algorithm for Minimum Spanning Tree\n");
    printf("=================================================================\n");

    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(V, E, edges);

    return 0;
}

/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 17: Breadth First Search (BFS) Traversal of a Graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20

typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++(q->rear)] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

void BFS(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Queue q;
    initQueue(&q);

    visited[startVertex] = true;
    enqueue(&q, startVertex);

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 17: Breadth First Search (BFS) Traversal\n");
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
        adjMatrix[v][u] = 1; // Undirected
    }

    BFS(adjMatrix, V, 0);
    BFS(adjMatrix, V, 2);

    return 0;
}

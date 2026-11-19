/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 06: Implementation of Circular Queue using Linked List
 * Operations: Enqueue, Dequeue, Display
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} CircularQueue;

void initQueue(CircularQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

bool isEmpty(CircularQueue *q) {
    return q->front == NULL;
}

void enqueue(CircularQueue *q, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
        newNode->next = newNode; // Points to itself
    } else {
        newNode->next = q->front;
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued %d into circular queue.\n", value);
}

int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Circular queue is empty.\n");
        return -1;
    }

    int value;
    if (q->front == q->rear) {
        // Only one element
        value = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    } else {
        Node *temp = q->front;
        value = temp->data;
        q->front = q->front->next;
        q->rear->next = q->front; // Maintain circular link
        free(temp);
    }
    printf("Dequeued %d from circular queue.\n", value);
    return value;
}

void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Circular queue is empty.\n");
        return;
    }
    printf("Circular Queue elements: ");
    Node *curr = q->front;
    do {
        printf("%d -> ", curr->data);
        curr = curr->next;
    } while (curr != q->front);
    printf("(circular back to front: %d)\n", q->front->data);
}

int main(void) {
    CircularQueue q;
    initQueue(&q);

    printf("=====================================================\n");
    printf(" Experiment 06: Circular Queue using Linked List\n");
    printf("=====================================================\n");

    enqueue(&q, 15);
    enqueue(&q, 25);
    enqueue(&q, 35);
    enqueue(&q, 45);
    display(&q);

    dequeue(&q);
    dequeue(&q);
    display(&q);

    enqueue(&q, 55);
    enqueue(&q, 65);
    display(&q);

    return 0;
}

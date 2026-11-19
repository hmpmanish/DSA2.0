/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 09: Implementation of Linear Queue using Linked List
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
} LinkedListQueue;

void initQueue(LinkedListQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

bool isEmpty(LinkedListQueue *q) {
    return q->front == NULL;
}

void enqueue(LinkedListQueue *q, int val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = val;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued %d into linked list queue.\n", val);
}

int dequeue(LinkedListQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Queue is empty.\n");
        return -1;
    }
    Node *temp = q->front;
    int val = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    printf("Dequeued %d from linked list queue.\n", val);
    return val;
}

void display(LinkedListQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue (Front to Rear): ");
    Node *curr = q->front;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main(void) {
    LinkedListQueue q;
    initQueue(&q);

    printf("=====================================================\n");
    printf(" Experiment 09: Linear Queue using Linked List\n");
    printf("=====================================================\n");

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    display(&q);

    dequeue(&q);
    dequeue(&q);

    display(&q);

    enqueue(&q, 50);
    enqueue(&q, 60);

    display(&q);

    return 0;
}

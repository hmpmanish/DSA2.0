/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO1
 * Experiment 03: Implementation of Linear Queue using Array
 * Operations: Enqueue, Dequeue, Peek, Display
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACITY 5

typedef struct {
    int items[CAPACITY];
    int front;
    int rear;
} LinearQueue;

void initQueue(LinearQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(LinearQueue *q) {
    return q->rear == CAPACITY - 1;
}

bool isEmpty(LinearQueue *q) {
    return q->front == -1 || q->front > q->rear;
}

void enqueue(LinearQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot insert %d (Queue is full).\n", value);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++(q->rear)] = value;
    printf("Enqueued %d to the queue.\n", value);
}

int dequeue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Queue is empty.\n");
        return -1;
    }
    int value = q->items[q->front++];
    printf("Dequeued %d from the queue.\n", value);
    if (q->front > q->rear) {
        // Reset when all elements are dequeued
        q->front = -1;
        q->rear = -1;
    }
    return value;
}

void display(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents (Front -> Rear): [ ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("]\n");
}

int main(void) {
    LinearQueue q;
    initQueue(&q);

    printf("=========================================\n");
    printf(" Experiment 03: Linear Queue using Array\n");
    printf("=========================================\n");

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    display(&q);

    // Overflow check
    enqueue(&q, 60);

    dequeue(&q);
    dequeue(&q);

    display(&q);

    return 0;
}

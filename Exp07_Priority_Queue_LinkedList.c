/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 07: Implementation of Priority Queue using Linked List
 * (Lower priority number indicates higher priority)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int priority; // Lower numerical value = Higher priority
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq) {
    pq->head = NULL;
}

bool isEmpty(PriorityQueue *pq) {
    return pq->head == NULL;
}

void enqueue(PriorityQueue *pq, int data, int priority) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    // If queue is empty or new node has higher priority than head
    if (isEmpty(pq) || priority < pq->head->priority) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        Node *curr = pq->head;
        while (curr->next != NULL && curr->next->priority <= priority) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    printf("Inserted data: %d with priority: %d\n", data, priority);
}

int dequeue(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue Underflow!\n");
        return -1;
    }
    Node *temp = pq->head;
    int data = temp->data;
    int prio = temp->priority;
    pq->head = pq->head->next;
    free(temp);
    printf("Dequeued highest priority element -> Data: %d (Priority: %d)\n", data, prio);
    return data;
}

void display(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty.\n");
        return;
    }
    printf("Priority Queue [Data(Priority)]: ");
    Node *curr = pq->head;
    while (curr != NULL) {
        printf("[%d(p=%d)] -> ", curr->data, curr->priority);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main(void) {
    PriorityQueue pq;
    initPriorityQueue(&pq);

    printf("=====================================================\n");
    printf(" Experiment 07: Priority Queue using Linked List\n");
    printf("=====================================================\n");

    // Insert elements with various priorities
    enqueue(&pq, 101, 3);
    enqueue(&pq, 202, 1); // highest priority
    enqueue(&pq, 303, 4);
    enqueue(&pq, 404, 2);
    enqueue(&pq, 505, 1);

    display(&pq);

    dequeue(&pq);
    dequeue(&pq);

    display(&pq);

    return 0;
}

/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 08: Implementation of Double Ended Queue (Deque) using Circular Array
 * Operations: InsertFront, InsertRear, DeleteFront, DeleteRear, Display
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEQUE_CAPACITY 6

typedef struct {
    int arr[DEQUE_CAPACITY];
    int front;
    int rear;
} Deque;

void initDeque(Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}

bool isFull(Deque *dq) {
    return ((dq->front == 0 && dq->rear == DEQUE_CAPACITY - 1) || (dq->front == dq->rear + 1));
}

bool isEmpty(Deque *dq) {
    return dq->front == -1;
}

void insertRear(Deque *dq, int val) {
    if (isFull(dq)) {
        printf("Deque Overflow at Rear! Cannot insert %d\n", val);
        return;
    }
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == DEQUE_CAPACITY - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    dq->arr[dq->rear] = val;
    printf("Inserted %d at Rear.\n", val);
}

void insertFront(Deque *dq, int val) {
    if (isFull(dq)) {
        printf("Deque Overflow at Front! Cannot insert %d\n", val);
        return;
    }
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = DEQUE_CAPACITY - 1;
    } else {
        dq->front--;
    }
    dq->arr[dq->front] = val;
    printf("Inserted %d at Front.\n", val);
}

int deleteFront(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow at Front!\n");
        return -1;
    }
    int val = dq->arr[dq->front];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == DEQUE_CAPACITY - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
    printf("Deleted %d from Front.\n", val);
    return val;
}

int deleteRear(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow at Rear!\n");
        return -1;
    }
    int val = dq->arr[dq->rear];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = DEQUE_CAPACITY - 1;
    } else {
        dq->rear--;
    }
    printf("Deleted %d from Rear.\n", val);
    return val;
}

void display(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is currently empty.\n");
        return;
    }
    printf("Deque contents: [ ");
    int i = dq->front;
    while (true) {
        printf("%d ", dq->arr[i]);
        if (i == dq->rear) break;
        i = (i + 1) % DEQUE_CAPACITY;
    }
    printf("]\n");
}

int main(void) {
    Deque dq;
    initDeque(&dq);

    printf("=====================================================\n");
    printf(" Experiment 08: Double Ended Queue (Deque)\n");
    printf("=====================================================\n");

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertFront(&dq, 2);

    display(&dq);

    deleteFront(&dq);
    display(&dq);

    deleteRear(&dq);
    display(&dq);

    insertRear(&dq, 30);
    insertRear(&dq, 40);
    display(&dq);

    return 0;
}

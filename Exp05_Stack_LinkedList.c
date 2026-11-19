/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 05: Implementation of Stack using Linked List
 * Operations: Push, Pop, Peek, Display
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} LinkedListStack;

void initStack(LinkedListStack *s) {
    s->top = NULL;
    s->size = 0;
}

bool isEmpty(LinkedListStack *s) {
    return s->top == NULL;
}

void push(LinkedListStack *s, int val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Stack Overflow.\n");
        return;
    }
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
    printf("Pushed %d onto linked list stack.\n", val);
}

int pop(LinkedListStack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow! Cannot pop from empty stack.\n");
        return -1;
    }
    Node *temp = s->top;
    int poppedVal = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    printf("Popped %d from linked list stack.\n", poppedVal);
    return poppedVal;
}

int peek(LinkedListStack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return s->top->data;
}

void display(LinkedListStack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (Top to Bottom):\n");
    Node *curr = s->top;
    while (curr != NULL) {
        printf(" [ %3d ] ->", curr->data);
        curr = curr->next;
    }
    printf(" NULL\n");
}

void freeStack(LinkedListStack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

int main(void) {
    LinkedListStack s;
    initStack(&s);

    printf("==============================================\n");
    printf(" Experiment 05: Stack using Linked List\n");
    printf("==============================================\n");

    push(&s, 100);
    push(&s, 200);
    push(&s, 300);
    display(&s);

    printf("Top element is: %d\n", peek(&s));

    pop(&s);
    display(&s);

    push(&s, 400);
    push(&s, 500);
    display(&s);

    freeStack(&s);
    return 0;
}

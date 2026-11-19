/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO1
 * Experiment 01: Implementation of Stack using Array
 * Operations: Push, Pop, Peek, and Display
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Error: Stack Overflow! Cannot push %d\n", value);
        return;
    }
    s->items[++(s->top)] = value;
    printf("Successfully pushed %d onto stack.\n", value);
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack Underflow! Stack is empty.\n");
        return -1;
    }
    int poppedValue = s->items[(s->top)--];
    printf("Successfully popped %d from stack.\n", poppedValue);
    return poppedValue;
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return s->items[s->top];
}

void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is currently empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = s->top; i >= 0; i--) {
        printf(" | %4d |\n", s->items[i]);
    }
    printf(" +------+\n");
}

int main(void) {
    Stack s;
    initStack(&s);

    printf("=========================================\n");
    printf(" Experiment 01: Stack using Array\n");
    printf("=========================================\n");

    // Demonstration of stack operations
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);

    display(&s);

    printf("Top element (peek): %d\n", peek(&s));

    pop(&s);
    pop(&s);

    display(&s);

    push(&s, 50);
    display(&s);

    return 0;
}

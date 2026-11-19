/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO1
 * Experiment 02: Convert Infix Expression into Postfix Expression using Stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 256

typedef struct {
    char items[MAX_SIZE];
    int top;
} CharStack;

void initStack(CharStack *s) {
    s->top = -1;
}

bool isEmpty(CharStack *s) {
    return s->top == -1;
}

void push(CharStack *s, char c) {
    if (s->top < MAX_SIZE - 1) {
        s->items[++(s->top)] = c;
    }
}

char pop(CharStack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(CharStack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

int precedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

bool isRightAssociative(char op) {
    return (op == '^');
}

void infixToPostfix(const char *infix, char *postfix) {
    CharStack s;
    initStack(&s);
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isspace((unsigned char)ch)) {
            continue;
        }

        // Operand (alphanumeric)
        if (isalnum((unsigned char)ch)) {
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            push(&s, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s); // remove '('
            }
        }
        else { // Operator
            while (!isEmpty(&s) && peek(&s) != '(') {
                char topOp = peek(&s);
                int precTop = precedence(topOp);
                int precCurr = precedence(ch);

                if (precTop > precCurr || (precTop == precCurr && !isRightAssociative(ch))) {
                    postfix[k++] = pop(&s);
                } else {
                    break;
                }
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        char op = pop(&s);
        if (op != '(' && op != ')') {
            postfix[k++] = op;
        }
    }
    postfix[k] = '\0';
}

int main(void) {
    printf("==================================================\n");
    printf(" Experiment 02: Infix to Postfix Conversion\n");
    printf("==================================================\n");

    const char *testCases[] = {
        "A + B * C",
        "(A + B) * (C - D)",
        "A + B * C / D - E ^ F ^ G",
        "((A + B) * C - (D - E)) ^ (F + G)"
    };
    int numTests = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTests; i++) {
        char postfix[MAX_SIZE];
        infixToPostfix(testCases[i], postfix);
        printf("\nTest Case %d:\n", i + 1);
        printf("  Infix   : %s\n", testCases[i]);
        printf("  Postfix : %s\n", postfix);
    }

    return 0;
}

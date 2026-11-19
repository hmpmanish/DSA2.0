/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 04: Evaluation of Postfix Expression using Stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define STACK_CAPACITY 100

typedef struct {
    double items[STACK_CAPACITY];
    int top;
} EvalStack;

void initStack(EvalStack *s) {
    s->top = -1;
}

bool isEmpty(EvalStack *s) {
    return s->top == -1;
}

void push(EvalStack *s, double val) {
    if (s->top < STACK_CAPACITY - 1) {
        s->items[++(s->top)] = val;
    }
}

double pop(EvalStack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return 0.0;
}

double evaluatePostfix(const char *expr) {
    EvalStack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (isspace((unsigned char)ch)) {
            continue;
        }

        if (isdigit((unsigned char)ch)) {
            // Support single digit or multi-digit reading
            double num = 0;
            while (isdigit((unsigned char)expr[i])) {
                num = num * 10 + (expr[i] - '0');
                if (isdigit((unsigned char)expr[i + 1])) {
                    i++;
                } else {
                    break;
                }
            }
            push(&s, num);
        } else {
            double op2 = pop(&s);
            double op1 = pop(&s);
            double result = 0.0;

            switch (ch) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/':
                    if (op2 == 0.0) {
                        printf("Error: Division by zero!\n");
                        return 0.0;
                    }
                    result = op1 / op2;
                    break;
                case '^': result = pow(op1, op2); break;
                default:
                    printf("Error: Unknown operator '%c'\n", ch);
                    return 0.0;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}

int main(void) {
    printf("==================================================\n");
    printf(" Experiment 04: Evaluation of Postfix Expression\n");
    printf("==================================================\n");

    const char *expressions[] = {
        "5 3 + 8 2 - *",            // (5+3) * (8-2) = 8 * 6 = 48
        "2 3 1 * + 9 -",            // 2 + (3*1) - 9 = 5 - 9 = -4
        "10 2 8 * + 3 -",           // 10 + (2*8) - 3 = 26 - 3 = 23
        "4 2 ^ 3 +"                 // 4^2 + 3 = 19
    };
    int count = sizeof(expressions) / sizeof(expressions[0]);

    for (int i = 0; i < count; i++) {
        double result = evaluatePostfix(expressions[i]);
        printf("Expression: %-20s => Result: %.2f\n", expressions[i], result);
    }

    return 0;
}

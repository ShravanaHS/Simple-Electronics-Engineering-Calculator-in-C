#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "math_ops.h"          // for parse_with_prefix()
#include "expression_eval.h"

/* -----------------------------------------------
   TOKENIZER
   ----------------------------------------------- */

#define MAX_TOKENS 256
#define MAX_LEN    32

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/* -----------------------------------------------
   Convert infix → postfix (Shunting Yard Algorithm)
   ----------------------------------------------- */

int infix_to_postfix(const char *expr, char postfix[][MAX_LEN]) {
    char opstack[128];
    int top = -1;
    int p = 0;

    for (int i = 0; expr[i]; ) {

        if (isspace(expr[i])) { i++; continue; }

        /* NUMBER / PREFIX TOKEN */
        if (isdigit(expr[i]) || expr[i] == '.') {
            int j = 0;
            while (isdigit(expr[i]) || expr[i]=='.' || isalpha(expr[i])) {
                postfix[p][j++] = expr[i++];
            }
            postfix[p][j] = '\0';
            p++;
        }

        /* LEFT PAREN */
        else if (expr[i] == '(') {
            opstack[++top] = expr[i];
            i++;
        }

        /* RIGHT PAREN */
        else if (expr[i] == ')') {
            while (top >= 0 && opstack[top] != '(') {
                postfix[p][0] = opstack[top--];
                postfix[p][1] = '\0';
                p++;
            }
            if (top >= 0 && opstack[top] == '(') top--;
            i++;
        }

        /* OPERATOR */
        else if (is_operator(expr[i])) {
            char op = expr[i];
            while (top >= 0 && is_operator(opstack[top]) &&
                   precedence(opstack[top]) >= precedence(op)) {
                postfix[p][0] = opstack[top--];
                postfix[p][1] = '\0';
                p++;
            }
            opstack[++top] = op;
            i++;
        }

        else {
            printf("Invalid character in expression.\n");
            return 0;
        }
    }

    /* POP REMAINING OPERATORS */
    while (top >= 0) {
        postfix[p][0] = opstack[top--];
        postfix[p][1] = '\0';
        p++;
    }

    return p;
}

/* -----------------------------------------------
   Evaluate postfix expression
   ----------------------------------------------- */

double eval_postfix(char postfix[][MAX_LEN], int count) {
    double stack[256];
    int top = -1;

    for (int i = 0; i < count; i++) {
        char *t = postfix[i];

        if (is_operator(t[0]) && strlen(t) == 1) {
            // operator
            double b = stack[top--];
            double a = stack[top--];

            switch (t[0]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        } 
        else {
            // number with prefix
            double val = parse_with_prefix(t);
            stack[++top] = val;
        }
    }

    return stack[top];
}

/* -----------------------------------------------
   Main API
   ----------------------------------------------- */

double evaluate_expression(const char *expr) {
    char postfix[MAX_TOKENS][MAX_LEN];
    int count = infix_to_postfix(expr, postfix);
    return eval_postfix(postfix, count);
}

/* -----------------------------------------------
   USER MENU
   ----------------------------------------------- */

void expression_menu(void) {
    char expr[256];

    printf("\n==== EXPRESSION EVALUATOR ====\n");
    printf("Supports: +  -  *  /  ( )  and prefixes like k,m,u,n,p\n");
    printf("Example: ((45k*33)+(22-21)/((45k-44k)*(23m+44k)))\n\n");

    printf("Enter expression: ");
    getchar();  // clear leftover newline
    fgets(expr, sizeof(expr), stdin);

    // Remove trailing newline
    expr[strcspn(expr, "\n")] = 0;

    double result = evaluate_expression(expr);

    printf("\nResult = %.10g\n", result);

    printf("Engineering Notation: ");
    print_with_prefix(result, "");
}

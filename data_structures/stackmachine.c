#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum sizes {
    stack_capacity=100000,
    buffer_size_operations=6
};


struct Stack {
    int *data;
    int capacity;
    int top;
};


void push(struct Stack *st, int x)
{
    st->data[st->top++] = x;
}


int pop(struct Stack *st)
{
    return st->data[--st->top];
}


void stack_add(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    push(st, a + b);
}


void stack_sub(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    push(st, a - b);
}


void stack_mul(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    push(st, a * b);
}


void stack_div(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    push(st, a / b);
}


void stack_max(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    if(a > b) {
        push(st, a);
    } else {
        push(st, b);
    }
}


void stack_min(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    if(a < b) {
        push(st, a);
    } else {
        push(st, b);
    }
}


void stack_neg(struct Stack *st)
{
    int a = pop(st);
    push(st, -a);
}


void stack_dup(struct Stack *st)
{
    int a = pop(st);
    push(st, a);
    push(st, a);
}


void stack_swap(struct Stack *st)
{
    int a = pop(st);
    int b = pop(st);
    push(st, a);
    push(st, b);
}


int scan_queries(struct Stack *st)
{
    int value;
    char input_oper[buffer_size_operations];
    scanf("%5s", input_oper);

    while(strcmp(input_oper, "END") != 0) {
        if(strcmp(input_oper, "CONST") == 0) {
            scanf(" %d", &value);
            push(st, value);
        } else if(strcmp(input_oper, "ADD") == 0) {
            stack_add(st);
        } else if(strcmp(input_oper, "SUB") == 0) {
            stack_sub(st);
        } else if(strcmp(input_oper, "MUL") == 0) {
            stack_mul(st);
        } else if(strcmp(input_oper, "DIV") == 0) {
            stack_div(st);
        } else if(strcmp(input_oper, "MAX") == 0) {
            stack_max(st);
        } else if(strcmp(input_oper, "MIN") == 0) {
            stack_min(st);
        } else if(strcmp(input_oper, "NEG") == 0) {
            stack_neg(st);
        } else if(strcmp(input_oper, "DUP") == 0) {
            stack_dup(st);
        } else if(strcmp(input_oper, "SWAP") == 0) {
            stack_swap(st);
        } else {
            printf("There is not such operation on stackmachine\n");
            return INT_MAX; 
        }
    scanf("%5s", input_oper);
    }

    return pop(st);
}


int main()
{
    int *data = calloc(stack_capacity, sizeof(int));
    struct Stack st = {data, stack_capacity, 0};
    int res = scan_queries(&st);
    if(res == INT_MAX) {
        free(data);
        return 1;
    }
    printf("%d\n", res);
    free(data);
    return 0;
}

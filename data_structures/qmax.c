#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum sizes {
    buffer_size_for_queue=10000000,
    buffer_size_operations=6
};


typedef struct {
    int *data;
    int *max;
    int capacity;
    int top1;
    int top2;
} DoubleStack;


int max(int a, int b)
{
    return a > b ? a : b;
}


void init_double_stack(DoubleStack *st, size_t length)
{
    st->data = calloc(length, sizeof(int));
    st->max = calloc(length, sizeof(int));
    st->capacity = length;
    st->top1 = 0;
    st->top2 = length - 1;
}


bool stack_empty_1(DoubleStack *st)
{
    if(st->top1 == 0) {
        return true;
    }
    return false;
}


bool stack_empty_2(DoubleStack *st)
{
    if(st->top2 == st->capacity - 1) {
        return true;
    }
    return false;
}


void push1(DoubleStack *st, int x)
{
    if(st->top2 < st->top1) {
        printf("overflow stack 1\n");
    }
    if(st->top1 == 0) {
        st->max[st->top1] = x;
    } else {
        st->max[st->top1] = max(st->max[st->top1 - 1], x);
    }
    st->data[st->top1++] = x;
}


void push2(DoubleStack *st, int x)
{
    if(st->top2 < st->top1) {
        printf("overflow stack 2\n");
    }
    if(st->top2 == (st->capacity - 1)) {
        st->max[st->top2] = x;
    } else {
        st->max[st->top2] = max(st->max[st->top2 + 1], x);
    }
    st->data[st->top2--] = x;
}


int pop1(DoubleStack *st)
{
    if(stack_empty_1(st)) {
        printf("devastation stack 1");
    }
    return st->data[--st->top1];
}


int pop2(DoubleStack *st)
{
    if(stack_empty_2(st)) {
        printf("devastation stack 2");
    }
    return st->data[++st->top2];
}


int stack_max_1(DoubleStack *st)
{
    return st->top1 == 0 ? INT_MIN : st->max[st->top1 - 1];
}


int stack_max_2(DoubleStack *st)
{
    return st->top2 == (st->capacity - 1) ? INT_MIN : st->max[st->top2 + 1];
}


void init_queue_on_stack(DoubleStack *st, size_t length)
{
    init_double_stack(st, length);
}


bool queue_empty(DoubleStack *st)
{
    if(stack_empty_1(st) && stack_empty_2(st)) {
        return true;
    }
    return false;
}


void enqueue(DoubleStack *st, int x)
{
    push1(st, x);
}


int dequeue(DoubleStack *st)
{
    if(stack_empty_2(st)) {
        while(!stack_empty_1(st)) {
            push2(st, pop1(st));
        }
    }
    return pop2(st);
}


int maximum(DoubleStack *st)
{
    return max(stack_max_1(st), stack_max_2(st));
}


void clean_up(DoubleStack *st)
{
    free(st->data);
    free(st->max);
}


void scan_queries(DoubleStack *st)
{
    int value;
    char input_oper[buffer_size_operations];
    scanf("%5s", input_oper);

    while(strcmp(input_oper, "END") != 0) {
        if(strcmp(input_oper, "ENQ") == 0) {
            scanf(" %d", &value);
            enqueue(st, value);
        } else if(strcmp(input_oper, "DEQ") == 0) {
            printf("%d\n", dequeue(st));
        } else if(strcmp(input_oper, "EMPTY") == 0) {
            printf("%s\n", queue_empty(st) ? "true" : "false");
        } else if(strcmp(input_oper, "MAX") == 0) {
            printf("%d\n", maximum(st));
        } else {
            printf("There is not such operation on circbuf\n");
            return; 
        }
    scanf("%5s", input_oper);
    }
}


int main()
{
    DoubleStack st;
    init_queue_on_stack(&st, buffer_size_for_queue);

    scan_queries(&st);

    clean_up(&st);
    return 0;
}

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum sizes {
    init_buffer_size_for_queue=4,
    buffer_size_operations=6
};


struct Queue {
    int *data;
    int capacity, tail, head, length;
};


void init_queue(struct Queue *que)
{
    int *data = calloc(init_buffer_size_for_queue, sizeof(int));
    que->data = data;
    que->capacity = init_buffer_size_for_queue;
    que->head = 0;
    que->tail = 0;
    que->length = 0;
}


bool queue_empty(struct Queue *que)
{
    if(que->length == 0) {
        return true;
    }
    return false;
}


void enqueue(struct Queue *que, int x)
{
    if(que->capacity == que->length) {
        int *new_data = calloc(que->capacity * 2, sizeof(int));
        for(int i = 0; i < que->length; i++) {
            new_data[i] = que->data[que->head++];
            if(que->head == que->capacity) {
                que->head = 0;
            }
        }
        free(que->data);
        que->data = new_data;
        que->capacity *= 2;
        que->head = 0;
        que->tail = que->length;
    }

    que->data[que->tail++] = x;
    if(que->tail == que->capacity) {
        que->tail = 0;
    }
    que->length++;
}


int dequeue(struct Queue *que)
{
    if(queue_empty(que)) {
        printf("Queue is empty\n");
        return INT_MAX;
    }

    int x = (que->data)[que->head++];
    if(que->head == que->capacity) {
        que->head = 0;
    }
    que->length--;
    return x;
}


void scan_queries(struct Queue *que)
{
    int value;
    char input_oper[buffer_size_operations];
    scanf("%5s", input_oper);

    while(strcmp(input_oper, "END") != 0) {
        if(strcmp(input_oper, "ENQ") == 0) {
            scanf(" %d", &value);
            enqueue(que, value);
        } else if(strcmp(input_oper, "DEQ") == 0) {
            int res = dequeue(que);
            if(res == INT_MAX) {
                return;
            }
            printf("%d\n", res);
        } else if(strcmp(input_oper, "EMPTY") == 0) {
            printf("%s\n", queue_empty(que) ? "true" : "false");
        } else {
            printf("There is not such operation on circbuf\n");
            return; 
        }
    scanf("%5s", input_oper);
    }
}


int main()
{
    struct Queue que;
    init_queue(&que);

    scan_queries(&que);

    free(que.data);
    return 0;
}

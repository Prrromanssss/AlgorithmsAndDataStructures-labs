#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Task {
    int time_from_turning_on;
    int time_of_completion_the_task;
};


typedef struct {
    int index;
    int key;
    struct Task value;
} HeapNode;


typedef struct {
    HeapNode **heap;
    int capacity;
    bool (*compare)(int a, int b);
    int length;
} PriorityQueue;


// Base functions

bool compare(int a, int b)
{
    return -a >= -b ? true : false;
}


void swap(PriorityQueue *pq, unsigned int i, unsigned int j)
{
    HeapNode *var_for_swapping = pq->heap[i];
    pq->heap[i] = pq->heap[j];
    pq->heap[j] = var_for_swapping;
}


int max(int a, int b)
{
    return a > b ? a : b;
}


// Functions to work with nodes

int left_node(unsigned int i)
{
    return 2 * i + 1;
}


int right_node(unsigned int i)
{
    return 2 * i + 2;
}


int parent_node(unsigned int i)
{
    return (i - 1) / 2;
}


void *init_heap_node(int index, int time_of_completion_the_task, int time_from_turning_on)
{
    struct Task value = {time_of_completion_the_task, time_from_turning_on};
    HeapNode *node = malloc(sizeof(HeapNode));
    node->index = index;
    node->value = value;
    node->key = value.time_of_completion_the_task + value.time_from_turning_on;
    return node;
}


// Funtions to work with priority queue

void init_priority_queue(PriorityQueue *pq, size_t length, 
                         bool (*compare)(int a, int b))
{
    pq->heap = calloc(length, sizeof(HeapNode *));
    pq->compare = compare;
    pq->length = 0;
    pq->capacity = length;
}


HeapNode *maximum(PriorityQueue *pq)
{
    if(pq->length == 0) {
        printf("Error: the priority queue is empty");
        return NULL;
    }
    return pq->heap[0];
}


bool queue_empty(PriorityQueue *pq)
{
    return pq->length == 0 ? true : false;
}


void insert(PriorityQueue *pq, HeapNode *node)
{
    int i = pq->length;
    if(i == pq->capacity) {
        printf("Error: overflow");
        return;
    }
    pq->length++;
    pq->heap[i] = node;
    while(i > 0 && compare(pq->heap[i]->key, pq->heap[parent_node(i)]->key)) {
        swap(pq, parent_node(i), i);
        pq->heap[i]->index = i;
        i = parent_node(i);
    }
    pq->heap[i]->index = i;
}


void heapify(PriorityQueue *pq, int i, int heap_size,
             bool (*compare)(int a, int b))
{
    int left = left_node(i);
    int right = right_node(i);
    int largest = -1;
    if(left < heap_size && compare(pq->heap[left]->key, pq->heap[i]->key)) {
        largest = left;
    } else {
        largest = i;
    }
    if(right < heap_size && compare(pq->heap[right]->key, pq->heap[largest]->key)) {
        largest = right;
    }
    if(largest != i) {
		swap(pq, i, largest);
        pq->heap[i]->index = i;
        pq->heap[largest]->index = largest;
		heapify(pq, largest, heap_size, compare);
	}
}


HeapNode *extract_max(PriorityQueue *pq)
{
    if(pq->length == 0) {
        printf("Error: overflow");
        return NULL;
    }
    HeapNode *max_node = pq->heap[0];
    pq->length--;
    if(pq->length > 0) {
        pq->heap[0] = pq->heap[pq->length];
        pq->heap[0]->index = 0;
        heapify(pq, 0, pq->length, pq->compare);
    }
    return max_node;
}


// Main algorithm

int get_min_time(PriorityQueue *pq, size_t number_of_tasks, size_t number_of_nodes)
{
    int min_time = 0;
    for(int i = 0; i < number_of_tasks; i++) {
        int t1, t2;
        scanf("%d %d", &t1, &t2);
        HeapNode *node = init_heap_node(i, t1, t2);
        if(pq->length != number_of_nodes) {
            insert(pq, node);
            min_time = max(min_time, node->key);
        } else {
            HeapNode *current_max_node = extract_max(pq);
            node->value.time_from_turning_on = max(current_max_node->key, node->value.time_from_turning_on);
            node->key = node->value.time_from_turning_on + node->value.time_of_completion_the_task;
            insert(pq, node);
            min_time = max(min_time, node->key);
            free(current_max_node);
        }
    }
    while(!queue_empty(pq)) {
        HeapNode *current_max_node = extract_max(pq);
        min_time = max(min_time, current_max_node->key);
        free(current_max_node);
    }
    return min_time;
}


int main()
{
    size_t number_of_nodes, number_of_tasks;
    scanf("%zu %zu", &number_of_nodes, &number_of_tasks);

    PriorityQueue pq;
    init_priority_queue(&pq, number_of_nodes, compare);

    printf("%d ", get_min_time(&pq, number_of_tasks, number_of_nodes));

    free(pq.heap);
    return 0;
}

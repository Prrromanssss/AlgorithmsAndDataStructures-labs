#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int index;
    int key;
    int *value;
    int index_for_key;
    int length_of_value;
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


void *init_heap_node(int index, int index_for_key, int length_of_value)
{
    HeapNode *node = malloc(sizeof(HeapNode));
    node->index = index;
    node->value = calloc(length_of_value, sizeof(int));
    for(int j = 0; j < length_of_value; j++) {
        scanf("%d", &(node->value[j]));
    }
    node->index_for_key = index_for_key;
    node->key = node->value[node->index_for_key];;
    node->length_of_value = length_of_value;
    return node;
}


void clean_node(HeapNode *node)
{
    free(node->value);
    free(node);
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


void heapify(PriorityQueue *pq, int i, int heap_size, size_t width,
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
		heapify(pq, largest, heap_size, width, compare);
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
    clean_node(pq->heap[0]);
    if(pq->length > 0) {
        pq->heap[0] = pq->heap[pq->length];
        pq->heap[0]->index = 0;
        heapify(pq, 0, pq->length, sizeof(HeapNode *), pq->compare);
    }
    pq->heap[pq->length] = NULL;
    return max_node;
}


void decrease_key(PriorityQueue *pq, HeapNode *node, int new_key)
{
    int i = node->index;
    node->key = new_key;
    heapify(pq, i, pq->length, sizeof(HeapNode *), pq->compare);
}


void clean_priority_queue(PriorityQueue *pq)
{
    for(int i = 0; i < pq->capacity; i++) {
        if(pq->heap[i] == NULL) {
            continue;
        }
        free(pq->heap[i]->value);
        free(pq->heap[i]);
    }
    free(pq->heap);
}


// Main algorithm

void merge(PriorityQueue *pq, size_t length)
{
    for(int i = 0; i < length; i++) {
        HeapNode *current_node = maximum(pq);
        printf("%d ", current_node->key);
        current_node->index_for_key++;
        if(current_node->index_for_key == current_node->length_of_value) {
            extract_max(pq);
        } else {
            decrease_key(pq, current_node, current_node->value[current_node->index_for_key]);
        }
    }

}


// Scanning functions

int scan_lengths_of_arrays(int lengths_of_arrays[], size_t number_of_arrays)
{
    int total_length = 0;
    for(int i = 0; i < number_of_arrays; i++) {
        scanf("%d", &lengths_of_arrays[i]);
        total_length += lengths_of_arrays[i];
    }
    return total_length;
}


void insert_init_values_in_queue(PriorityQueue *pq, int lengths_of_arrays[], size_t number_of_arrays)
{
    for(int i = 0; i < number_of_arrays; i++) {
        HeapNode *node = init_heap_node(i, 0, lengths_of_arrays[i]);
        insert(pq, node);
    }

}


int main()
{
    PriorityQueue pq;
    int number_of_arrays;
    size_t total_length;
    scanf("%d", &number_of_arrays);

    init_priority_queue(&pq, number_of_arrays, compare);

    int lengths_of_arrays[number_of_arrays];
    total_length = scan_lengths_of_arrays(lengths_of_arrays, number_of_arrays);

    insert_init_values_in_queue(&pq, lengths_of_arrays, number_of_arrays);

    merge(&pq, total_length);

    clean_priority_queue(&pq);
    return 0;
}

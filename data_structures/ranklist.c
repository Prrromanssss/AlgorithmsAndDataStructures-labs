#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum sizes {
    height=20,
    buffer_size_for_input=7,
    buffer_size_for_value=11
};


typedef struct Elem {
    int key;
    char *value;
    struct Elem **next;
    int *span;
} SkipListNode;


SkipListNode *init_skip_list(size_t height)
{
    SkipListNode *list = malloc(sizeof(SkipListNode));
    list->next = calloc(height, sizeof(SkipListNode *));
    list->span = calloc(height, sizeof(int));
    list->key = INT_MIN;
    list->value = NULL;
    for(int i = 0; i < height; i++) {
        list->next[i] = NULL;
    }
    return list;
}


bool map_empty(SkipListNode *list)
{
    return list->next[0] == NULL ? true : false;
}


SkipListNode *succ_skip_list(SkipListNode *node)
{
    return node->next[0];
}


void skip_skip_list(SkipListNode *list, size_t height, int key, SkipListNode **pointers)
{
    SkipListNode *x = list;
    for(int i = height - 1; i >= 0; i--) {
        while(x->next[i] != NULL && x->next[i]->key < key) {
            x = x->next[i];
        }
        pointers[i] = x;
    }
}


int rank_skip_list(SkipListNode *list, size_t height, int key)
{
    if(key == INT_MIN) {
        return -1;
    }
    int index = 0;
    SkipListNode *x = list;
    for(int i = height - 1; i >= 0; i--) {
        while(x->next[i] != NULL && x->next[i]->key < key) {
            index += x->span[i];
            x = x->next[i];
        }
    }
    return index;
}


void insert_skip_list(SkipListNode *list, size_t height, int key, char *value)
{
    SkipListNode *pointers[height];
    skip_skip_list(list, height, key, pointers);
    if(pointers[0]->next[0] != NULL && pointers[0]->next[0]->key == key) {
        printf("Error: insert skip list");
        exit(2);
    }
    SkipListNode *new_node = init_skip_list(height);
    new_node->key = key;
    new_node->value = value;
    long long number_of_lists_will_include_new_node = rand() * 2ll;
    int rank_new_node = rank_skip_list(list, height, pointers[0]->key) + 1;
    int i;
    for(i = 0; i < height && number_of_lists_will_include_new_node % 2 == 0; i++) {
        new_node->next[i] = pointers[i]->next[i];
        pointers[i]->next[i] = new_node;
        int rank_node_i = rank_skip_list(list, height, pointers[i]->key);
        new_node->span[i] = pointers[i]->span[i] + 1 - rank_new_node + rank_node_i;
        pointers[i]->span[i] = rank_new_node - rank_node_i;
        number_of_lists_will_include_new_node /= 2;
    }
    for(; i < height; i++) {
        pointers[i]->span[i]++;
    }
}


char *lookup_skip_list(SkipListNode *list, size_t height, int key)
{
    SkipListNode *pointers[height];
    skip_skip_list(list, height, key, pointers);
    SkipListNode *res = succ_skip_list(pointers[0]);
    if(res == NULL || res->key != key) {
        printf("Error: lookup skip list");
        exit(1);
    }
    return res->value;
}


void clean_up_node(SkipListNode *node)
{
    free(node->value);
    free(node->next);
    free(node->span);
    free(node);
}


void delete_skip_list(SkipListNode *list, size_t height, int key)
{
    SkipListNode *pointers[height];
    skip_skip_list(list, height, key, pointers);
    SkipListNode *res = succ_skip_list(pointers[0]);
    if(res == NULL || res->key != key) {
        printf("Error: delete skip list");
        exit(3);
    }
    int i;
    for(i = 0; i < height && pointers[i]->next[i] == res; i++) {
        pointers[i]->span[i] += res->span[i] - 1;
        pointers[i]->next[i] = res->next[i];
    }

    for(; i < height; i++) {
        pointers[i]->span[i]--;
    }
    clean_up_node(res);
}


void cleanup_skip_list(SkipListNode *list)
{
    while(list) {
        SkipListNode *temp_node = list->next[0];
        if(list->value) {
            free(list->value);
        }
        free(list->next);
        free(list->span);
        free(list);
        list = temp_node;
    }
}


void scan_queries(SkipListNode *list)
{
    int key;
    char input_oper[buffer_size_for_input];
    scanf("%6s", input_oper);
    while(strcmp(input_oper, "END") != 0) {
        scanf("%d", &key);
        if(strcmp(input_oper, "INSERT") == 0) {
            char *value = malloc(buffer_size_for_value);
            scanf("%s", value);
            insert_skip_list(list, height, key, value);
        } else if(strcmp(input_oper, "LOOKUP") == 0) {
            printf("%s\n", lookup_skip_list(list, height, key));
        } else if(strcmp(input_oper, "DELETE") == 0) {
            delete_skip_list(list, height, key);
        } else if(strcmp(input_oper, "RANK") == 0) {
            printf("%d\n", rank_skip_list(list, height, key));
        } else {
            printf("There is not such operation in skiplist\n");
            return; 
        }
        scanf("%6s", input_oper);
    }

}


int main()
{
    SkipListNode *list = init_skip_list(height);

    scan_queries(list);

    cleanup_skip_list(list);
    return 0;
}
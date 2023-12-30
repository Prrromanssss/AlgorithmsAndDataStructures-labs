#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode {
    struct ListNode *prev, *next;
    int value;
} node_l;


node_l *init_double_linked_list()
{
    node_l *node = malloc(sizeof(node_l));
    node->next = node;
    node->prev = node;
    node->value = INT_MAX;
    return node;
}


void insert_after_tail(node_l *list, int value)
{
    node_l *node = malloc(sizeof(node_l));
    node->value = value;
    node->next = list->next;
    node->prev = list;
    list->next = node;
}


void delete_and_insert_after_node(node_l *node1, node_l *node2)
{
    // Delete node1
    node1->prev->next = node1->next;
    node1->next->prev = node1->prev;

    // Insert node1 after node2
    node1->next = node2->next;
    node1->prev = node2;
    node2->next->prev = node1;
    node2->next = node1;
}


void insertion_sort(node_l *list)
{
    node_l *i = list->next->next;
    while(i != list) {
        node_l *new_node = i->next;
        int elem = i->value;
        node_l *loc = i->prev;
        while(loc != list && loc->value > elem) {
            loc = loc->prev;
        }
        delete_and_insert_after_node(i, loc);
        i = new_node;
    }
}


void scan_double_linked_list(node_l *list, size_t length)
{
    int num;
    node_l *tail = list;
    for(int i = 0; i < length; i++) {
        scanf("%d", &num);
        insert_after_tail(tail, num);
        tail = tail->next;
    }
}


void print_double_linked_list(node_l *list)
{
    node_l *i = list->next;
    while(i != list) {
        printf("%d ", i->value);
        i = i->next;
    }
    printf("\n");
}


void clean_up_double_linked_list(node_l *list)
{
    node_l *i = list->next;
    while(i != list) {
        node_l *temp_node = i;
        i = i->next;
        free(temp_node); 
    }
    free(list);
}


int main()
{
    int n;
    scanf("%d", &n);

    node_l *list = init_double_linked_list();
    scan_double_linked_list(list, n);
    insertion_sort(list);
    print_double_linked_list(list);
    clean_up_double_linked_list(list);
    return 0;
}

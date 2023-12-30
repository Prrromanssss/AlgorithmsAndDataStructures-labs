#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 1001


typedef struct Elem {
	struct Elem *next;
	char *word;
} ListNode;


ListNode *init_single_linked_list()
{
    return NULL;
}


void insert_after(ListNode *node1, ListNode *node2)
{
    ListNode *temp_node = node1->next;
    node1->next = node2;
    node2->next = temp_node;
}


ListNode *make_node(ListNode *next, char *word)
{
    ListNode *node = malloc(sizeof(ListNode));
    if(next == NULL) {
        node->next = next;
    } else {
        insert_after(next, node);
    }
    node->word = word;
    return node;
}


ListNode *fill_single_linked_list(ListNode *list, char *src)
{
    ListNode *head = list;
    int init_size = strlen(src);
    char delim[] = " ";
    char *field = strtok(src, delim);

    while (field != NULL) {
        if(field[strlen(field) - 1] == '\n') {
            field[strlen(field) - 1] = '\0';
        }
        ListNode *node = make_node(list, field);
        if(list == NULL) {
            list = node;
            head = node;
        } else {
            list = list->next;
        }
        field = strtok(NULL, delim);
    }
    return head;
}


void swap_nodes(ListNode *node)
{
    ListNode *temp_node = node->next->next;
    node->next->next = node;
    node->next = temp_node;
}


ListNode *bsort(ListNode *list)
{
    ListNode *right_node = NULL;
    while(right_node != list) {
        ListNode *prev_node = NULL;
        ListNode *j_node = list;
        while(j_node->next != right_node) {
            if(strlen(j_node->word) > strlen(j_node->next->word)) {
                ListNode *next_j_node = j_node->next;
                if(prev_node != NULL) {
                    prev_node->next = j_node->next;
                    swap_nodes(j_node);
                } else {
                    list = j_node->next;
                    swap_nodes(j_node);
                }
                j_node = next_j_node;
            }
            prev_node = j_node;
            j_node = j_node->next;
        }
        right_node = j_node;
    }
    return list;
}


void print_single_linked_list(ListNode *list)
{
    while(list) {
        printf("%s ", list->word);
        list = list->next;
    }
    printf("\n");
}


void clean_up_single_linked_list(ListNode *list)
{
    while(list) {
        ListNode *current_node = list;
        list = list->next;
        free(current_node);
    }
}


int main()
{
    char sentence[BUFFER_SIZE];
    fgets(sentence, BUFFER_SIZE, stdin);
    ListNode *list = init_single_linked_list();
    list = fill_single_linked_list(list, sentence);
    list = bsort(list);
    print_single_linked_list(list);
    clean_up_single_linked_list(list);
    return 0;
}

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum sizes {
    stack_capacity=100000,
    buffer_size_for_input=7,
    buffer_size_for_value=11
};


typedef struct StringWithLength {
    char *data;
    size_t length;
} str_l;


typedef struct BinarySearchTreeNode {
    int key;
    str_l value;
    struct BinarySearchTreeNode *parent;
    struct BinarySearchTreeNode *left;
    struct BinarySearchTreeNode *right;
    int rank;
} BSTNode;


typedef struct Stack {
    int *data;
    int capacity;
    int top;
} stack;


BSTNode *init_binary_tree_search()
{
    BSTNode *tree = malloc(sizeof(BSTNode));
    tree->parent = NULL;
    return tree;
}


void insert_binary_tree_search(BSTNode *tree, int key, str_l value)
{
    BSTNode *node = malloc(sizeof(BSTNode));
    node->key = key;
    node->value = value;
    node->rank = 0;
    node->left = NULL;
    node->right = NULL;
    if(tree->parent == NULL) {
        tree->parent = node;
        node->parent = NULL;
        return;
    }
    BSTNode *parent = tree->parent;
    while (true) {
        if(key < parent->key) {
            if (parent->left == NULL) {
              parent->rank++;
              parent->left = node;
              node->parent = parent;
              break;
            }
            parent->rank++;
            parent = parent->left;
        } else {
            if (parent->right == NULL) {
                parent->right = node;
                node->parent = parent;
                break;
            }
            parent = parent->right;
        }
    }
}


BSTNode *descend_binary_tree_search(BSTNode *tree, int key)
{
    BSTNode *res = tree->parent;
    while(res != NULL && res->key != key) {
        if(res->key < key) {
            res = res->right;
        } else {
            res = res->left;
        }
    }
    return res->key == key ? res : NULL;
}


BSTNode *lookup_binary_tree_search(BSTNode *tree, int key)
{
    BSTNode *res = descend_binary_tree_search(tree, key);
    if(res == NULL) {
        printf("Panic: lookup does not find sth");
        exit(1);
    }
    return res;
}


BSTNode *minimum_binary_tree_search(BSTNode *tree)
{
    if(tree == NULL) {
        return NULL;
    }
    BSTNode *node = tree;
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}


BSTNode *succ_binary_tree_search(BSTNode *node)
{
    if(node->right != NULL) {
        return minimum_binary_tree_search(node->right);
    }
    BSTNode *node_parent = node->parent;
    while(node_parent != NULL && node == node_parent->right) {
        node = node_parent;
        node_parent = node_parent->parent;
    }
    return node_parent;
}


void decrease_rank_binary_tree_search(BSTNode *node)
{
    while(node != NULL && node->parent) {
        if(node->parent->left == node) {
            node->parent->rank--;
        }
        node = node->parent;
    }
}


void clean_up_node_binary_tree_search(BSTNode *node)
{
    free(node->value.data);
    free(node);
}


void replace_node_binary_tree_search(BSTNode *tree, BSTNode *old_node, BSTNode *new_node)
{
    if(tree->parent == old_node) {
        tree->parent = new_node;
        if(new_node != NULL) {
            new_node->parent = NULL;
        }
        return;
    }
    if(old_node->parent->right == old_node) {
        old_node->parent->right = new_node;
    } else {
        old_node->parent->left = new_node;
    }
    if(new_node != NULL) {
        new_node->parent = old_node->parent;
    }
}


void delete_binary_tree_search(BSTNode *tree, int key)
{
    BSTNode *node_to_remove =lookup_binary_tree_search(tree, key);
    if(node_to_remove->left == NULL && node_to_remove->right == NULL) {
        decrease_rank_binary_tree_search(node_to_remove);
        replace_node_binary_tree_search(tree, node_to_remove, NULL);
    } else if(node_to_remove->left == NULL) {
        decrease_rank_binary_tree_search(node_to_remove);
        replace_node_binary_tree_search(tree, node_to_remove, node_to_remove->right);
    } else if(node_to_remove->right == NULL) {
        decrease_rank_binary_tree_search(node_to_remove);
        replace_node_binary_tree_search(tree, node_to_remove, node_to_remove->left);
    } else {
        BSTNode *succ_node = succ_binary_tree_search(node_to_remove);
        decrease_rank_binary_tree_search(node_to_remove);
        replace_node_binary_tree_search(tree, succ_node, succ_node->right);
        replace_node_binary_tree_search(tree, node_to_remove, succ_node);
        succ_node->rank = node_to_remove->rank;
        succ_node->left = node_to_remove->left;
        succ_node->left->parent = succ_node;
        if(node_to_remove->right != NULL) {
            succ_node->right = node_to_remove->right;
            succ_node->right->parent = succ_node;
        }
    }
    clean_up_node_binary_tree_search(node_to_remove);
}


str_l search_by_rank_binary_tree_search(BSTNode *tree, int rank)
{
    BSTNode *res = tree->parent;
    while (res->rank != rank) {
        if (rank > res->rank) {
            rank -= res->rank + 1;
            res = res->right;
        } else {
            res = res->left;
        }
    }
    return res->value;
}


stack *init_stack()
{
    stack *new = malloc(sizeof(stack));
    new->capacity = stack_capacity;
    new->top = 0;
    new->data = calloc(stack_capacity, sizeof(BSTNode *));
    return new;
}


void push_stack(stack *st, BSTNode *x)
{
    st->data[st->top++] = x;
}


bool empty_stack(stack *st)
{
    return st->top == 0 ? true : false;
}


BSTNode *pop_stack(stack *st)
{
    return st->data[--st->top];
}


void clean_up_stack(stack *st)
{
    free(st->data);
    free(st);
}


void clean_up_binary_tree_search(BSTNode *tree)
{
    BSTNode *parent = tree->parent;
    stack *st = init_stack();
    push_stack(st, parent);
    while(!empty_stack(st)) {
        BSTNode *temp_node = pop_stack(st);
        if(temp_node != NULL) {
            push_stack(st, temp_node->left);
            push_stack(st, temp_node->right);
            clean_up_node_binary_tree_search(temp_node);
        }
    }
    clean_up_stack(st);
    free(tree);
}


void scan_queries(BSTNode *tree)
{
    int key;
    char input_oper[buffer_size_for_input];
    scanf("%6s", input_oper);
    while(strcmp(input_oper, "END") != 0) {
        scanf("%d", &key);
        if(strcmp(input_oper, "INSERT") == 0) {
            char *value_data = malloc(buffer_size_for_value);
            scanf("%s", value_data);
            str_l value = {value_data, strlen(value_data)};
            insert_binary_tree_search(tree, key, value);
        } else if(strcmp(input_oper, "LOOKUP") == 0) {
            printf("%s\n", lookup_binary_tree_search(tree, key)->value.data);
        } else if(strcmp(input_oper, "DELETE") == 0) {
            delete_binary_tree_search(tree, key);
        } else if(strcmp(input_oper, "SEARCH") == 0) {
            printf("%s\n", search_by_rank_binary_tree_search(tree, key).data);
        } else {
            printf("There is not such operation in skiplist\n");
            return; 
        }
        scanf("%6s", input_oper);
    }
}


int main()
{
    BSTNode *tree = init_binary_tree_search();
    scan_queries(tree);
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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


BSTNode *init_binary_tree_search()
{
    BSTNode *tree = malloc(sizeof(BSTNode));
    tree->parent = NULL;
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


void delete_binary_tree_search()
{

}


void replace_node_binary_tree_search()
{

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


void scan_queries()
{

}


int main()
{

}
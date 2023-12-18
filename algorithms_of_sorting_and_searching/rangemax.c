#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 20


int max(int a, int b)
{
    return a > b ? a : b;
}


int query(int tree[], int left, int right, int i, int a, int b)
{
    if(left == a && right == b) {
        return tree[i];
    }

    int mid = (a + b) / 2;
    if(right <= mid) {
        return query(tree, left, right, 2 * i + 1, a, mid);
    } else if(left > mid) {
        return query(tree, left, right, 2 * i + 2, mid + 1, b);
    } else {
        return max(query(tree, left, mid, 2 * i + 1, a, mid),
               query(tree, mid + 1, right, 2 * i + 2, mid + 1, b));
    }
}


void build(int segm[], int i, int a, int b, int tree[])
{
    if(a == b) {
        tree[i] = segm[a];
    } else {
        int mid = (a + b) / 2;
        build(segm, 2 * i + 1, a, mid, tree);
        build(segm, 2 * i + 2, mid + 1, b, tree);
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}


void update(int j, int new_value, int i, int a, int b, int tree[])
{
    if(a == b) {
        tree[i] = new_value;
    } else {
        int mid = (a + b) / 2;
        if(j <= mid) {
            update(j, new_value, 2 * i + 1, a, mid, tree);
        } else {
            update(j, new_value, 2 * i + 2, mid + 1, b, tree);
        }
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}


int segment_tree_query(int tree[], int length, int left, int right)
{
    return query(tree, left, right, 0, 0, length - 1);
}


void segment_tree_build(int segm[], int tree[], int length)
{
    build(segm, 0, 0, length - 1, tree);
}


void segment_tree_update(int j, int new_value, int length, int tree[])
{
    update(j, new_value, 0, 0, length - 1, tree);
}


void init_tree(int tree[], size_t length)
{
    for(int i = 0; i < 4 * length; i++) {
        tree[i] = 0;
    }
}


void scan_segment(int segment[], size_t length)
{
    for(int i = 0; i < length; i++) {
        scanf("%d", &segment[i]);
    }
}


void scan_queries(int tree[], size_t length)
{
    int left, right, i, new_value;
    char input[BUFFER_SIZE];
    scanf("%3s", input);

    while(strcmp(input, "END") != 0) {
        if(strcmp(input, "MAX") == 0) {
            scanf(" %d %d", &left, &right);
            printf("%d\n", segment_tree_query(tree, length, left, right));
        } else if(strcmp(input, "UPD") == 0) {
            scanf(" %d %d", &i, &new_value);
            segment_tree_update(i, new_value, length, tree);
        }
    scanf("%3s", input);
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    int *tree = calloc(4 * n, sizeof(int));
    init_tree(tree, n);

    int *segment = calloc(n, sizeof(int));
    scan_segment(segment, n);

    segment_tree_build(segment, tree, n);
    scan_queries(tree, n);

    free(tree);
    free(segment);
    return 0;
}

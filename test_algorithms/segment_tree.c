#include <stdint.h>
#include <stdio.h>


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
        return query(tree, left, mid, 2 * i + 1, a, mid) +
               query(tree, mid + 1, right, 2 * i + 2, mid + 1, b);
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
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
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
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
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


int main()
{
    int n = 10;
    int tree[4 * n];
    for(int i = 0; i < 4 * n; i++) {
        tree[i] = 0;
    }
    int segment[10] = {2, 3, 5, 1, 0, 4, 7, 6, 2, 3};
    segment_tree_build(segment, tree, n);


    printf("%d\n", segment_tree_query(tree, n, 2, 4));
    segment_tree_update(2, 100, n, tree);
    printf("%d\n", segment_tree_query(tree, n, 2, 4));


    return 0;
}

#include <stdio.h>
#include <math.h>

int min(int a, int b)
{
    return a < b ? a : b;
}


int query(int tree[], int i)
{
    int res = 0;
    while(i >= 0) {
        res += tree[i];
        i = (i & (i + 1)) - 1;
    }
    return res;
}


int fenwick_tree_query(int tree[], int left, int right)
{
    return query(tree, right) - query(tree, left - 1);
}


void fenwick_tree_update(int tree[], int i, int add_elem, int length)
{
    while(i < length) {
        tree[i] += add_elem;
        i = i | (i + 1);
    }
}


int build(int tree[], int segment[], int left, int right, int length)
{
    int sum = 0, mid;
    int bound = min(right, length);
    while(left < bound) {
        mid = (left + right) / 2;
        sum += build(tree, segment, left, mid, length);
        left = mid + 1;
    }
    if(right < length)
    {
        sum += segment[right];
        tree[right] = sum;
    }
    return sum;
}


void fenwick_tree_build(int tree[], int segment[], int length)
{
    int right = pow(2, ceil(log2(length)));
    build(tree, segment, 0, right - 1, length);
}


int main()
{
    int n = 10;
    int tree[n];
    int segment[] = {0, 0, 0, 0, 1, 0, 0, 1, 0, 1};
    fenwick_tree_build(tree, segment, n);
    printf("%d", fenwick_tree_query(tree, 0, 8));
}
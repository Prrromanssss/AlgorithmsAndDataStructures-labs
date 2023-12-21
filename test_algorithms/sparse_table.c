#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int min(int a, int b)
{
    return a < b ? a : b;
}


int log2i(int a) {
    return 31 - __builtin_clz((unsigned int)a);
}


int sparse_table_query(int **st, int left, int right)
{
    int j = log2i(right - left + 1);
    return min(st[left][j], st[right - (int)pow(2, j) + 1][j]);
}


void sparse_table_build(int segment[], int **st, size_t length)
{
    int m = log2i(length) + 1;

    for(int i = 0; i < length; i++) {
        st[i][0] = segment[i];
    }

    for(int j = 1; j < m; j++) {
        for(int i = 0; i <= length - (int)pow(2, j); i++) {
            st[i][j] = min(st[i][j - 1], st[i + (int)pow(2, j - 1)][j - 1]);
        }
    }
}


int main()
{
    int length = 11;
    int m = log2i(length);
    int segment[] = {6, 4, 7, 1, 2, 4, 9, 2, 1, 7, 6};
    int **st = calloc(length, sizeof(int *));
    for(int i = 0; i < length; i++) {
        st[i] = calloc(m + 1, sizeof(int));
    }

    sparse_table_build(segment, st, length);


    printf("%d ", sparse_table_query(st, 0, 2));

    for(int i = 0; i < length; i++) {
        free(st[i]);
    }
    free(st);
}
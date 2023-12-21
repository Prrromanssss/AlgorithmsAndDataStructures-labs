#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int gcd(int a, int b)
{
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}


int log2clz(int a)
{
    return 31 - __builtin_clz((unsigned int)a);
}


int sparse_table_query(int **st, int left, int right)
{
    int j = log2clz(right - left + 1);
    return gcd(st[left][j], st[right - (1 << j) + 1][j]);
}


void sparse_table_build(int **st, size_t length)
{
    int cols = log2clz(length) + 1;

    for(int j = 1; j < cols; j++) {
        for(int i = 0; i <= length - (1 << j); i++) {
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}


void init_parse_table(int **st, int cols, size_t length)
{
    int num;
    for(int i = 0; i < length; i++) {
        scanf("%d", &num);
        st[i] = calloc(cols + 1, sizeof(int));
        st[i][0] = abs(num);
    }
}


void scan_queries(int **st)
{
    int count_queries, left, right;
    scanf("%d", &count_queries);

    for(int i = 0; i < count_queries; i++) {
        scanf("%d %d", &left, &right);
        printf("%d\n", sparse_table_query(st, left, right));
    }
}


void clean_up(int **st, size_t length)
{
    for(int i = 0; i < length; i++) {
        free(st[i]);
    }
    free(st);
}


int main()
{
    int length;
    scanf("%d", &length);
    int cols = log2clz(length);

    int **st = calloc(length, sizeof(int *));
    init_parse_table(st, cols, length);
    sparse_table_build(st, length);

    scan_queries(st);

    clean_up(st, length);
    return 0;
}

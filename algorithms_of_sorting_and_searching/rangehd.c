#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum BUFFER_SIZE {
    buffer_size_for_input=5,
    buffer_size_for_substring=1000001,
    buffer_size_for_segment=1000001
};


int min(int a, int b)
{
    return a < b ? a : b;
}


int query(int tree[], int i)
{
    int res = 0;
    while(i >= 0) {
        res ^= tree[i];
        i = (i & (i + 1)) - 1;
    }
    return res;
}


int build(int tree[], char *segment, int left, int right, int length)
{
    int sum = 0, mid;
    int bound = min(right, length);
    while(left < bound) {
        mid = (left + right) / 2;
        sum ^= build(tree, segment, left, mid, length);
        left = mid + 1;
    }
    if(right < length)
    {
        sum ^= (1 << (segment[right] -'a'));
        tree[right] = sum;
    }

    return sum;
}


int fenwick_tree_query(int tree[], int left, int right)
{
    return query(tree, right) ^ query(tree, left - 1);
}


void fenwick_tree_update(int tree[], int i, int add_elem, int length)
{
    while(i < length) {
        tree[i] ^= add_elem;
        i = i | (i + 1);
    }
}


void fenwick_tree_update_sequence(int tree[], char segment[], char *new_s,
                                  int i, int length, int length_to_upd)
{
    int j = i;
    for(int i = j; i < length_to_upd; i++) {
        fenwick_tree_update(tree, i, (1 << (segment[i] - 'a')) ^ (1 << (new_s[i - j] - 'a')), length);
    }
}


void fenwick_tree_build(int tree[], char *segment, int length)
{
    int right = pow(2, ceil(log2(length)));
    build(tree, segment, 0, right - 1, length);
}


void scan_queries(int tree[], char *segment, size_t length)
{
    int left, right, i;
    char *new_str = calloc(buffer_size_for_substring, sizeof(char));
    char input[buffer_size_for_input];
    scanf("%3s", input);

    while(strcmp(input, "END") != 0) {
        if(strcmp(input, "HD") == 0) {
            scanf(" %d %d", &left, &right);
            int res = fenwick_tree_query(tree, left, right);
            if((left - right + 1) % 2) {
                printf((res & (res - 1)) ? "NO\n" : "YES\n");
            } else {
                printf(res ? "NO\n" : "YES\n");
            }
        } else if(strcmp(input, "UPD") == 0) {
            scanf(" %d %s", &i, new_str);
            fenwick_tree_update_sequence(tree, segment, new_str, i, length, i + strlen(new_str));
            memcpy(&segment[i], new_str, strlen(new_str));
        }
    scanf("%3s", input);
    }
    free(new_str);
}


int main()
{
    char *segment = calloc(buffer_size_for_segment, sizeof(char));
    scanf("%s", segment);

    int n = strlen(segment);
    int *tree = calloc(n, sizeof(int));

    fenwick_tree_build(tree, segment, n);
    scan_queries(tree, segment, n);

    free(tree);
    free(segment);
    
    return 0;
}

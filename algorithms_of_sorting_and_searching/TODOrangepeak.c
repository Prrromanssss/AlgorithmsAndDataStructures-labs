#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 5


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


int build(int tree[], int segment[], int left, int right, size_t length)
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


void update(int tree[], int i, int add_value, size_t length)
{
    while(i < length) {
        tree[i] += add_value;
        i = i | (i + 1);
    }
}


// Functions to work with array of peaks

void make_peak(int peak[], int segment[], size_t length)
{
    if(length == 1) {
        peak[0] = 0;
        return;
    }
    for(int i = 0; i < length; i++) {
        if((i == 0 || segment[i] >= segment[i - 1]) &&
           (i == length - 1 || segment[i] >= segment[i + 1])) {
            peak[i] = 1;
        } else {
            peak[i] = 0;
        }
    }
}


void update_peak(int peak[], int segment[], int i, size_t length)
{
    if(length >= 1 && length < 5) {
        make_peak(peak, segment, length);
    } else if(i == 0) {
        for(int j = i; j < i + 2; j++) {
            if((j == i || segment[j] >= segment[j - 1]) &&
               segment[j] >= segment[j + 1]) {
                peak[j] = 1;
            } else {
                peak[j] = 0;
            }
        }
    } else if(i == length - 1) {
        for(int j = i - 1; j < i + 1; j++) {
            if(segment[j] >= segment[j - 1] &&
               (j == i || segment[j] >= segment[j + 1])) {
                peak[j] = 1;
            } else {
                peak[j] = 0;
            }
        }
    } else {
        for(int j = i - 1; j < i + 2; j++) {
            if(segment[j] >= segment[j - 1] &&
               segment[j] >= segment[j + 1]) {
                peak[j] = 1;
            } else {
                peak[j] = 0;
            }
        }
    }
}


// Functions to work with Fenwick tree

int fenwick_tree_query(int tree[], int left, int right)
{
    return query(tree, right) - query(tree, left - 1);
}


void fenwick_tree_build(int tree[], int segment[], size_t length)
{
    int right = pow(2, ceil(log2(length)));
    build(tree, segment, 0, right - 1, length);
}


void fenwick_tree_update(int tree[], int segment[], int peak[], int i, int new_value, size_t length)
{
    segment[i] = new_value;

    int old_i_value = peak[i];
    int old_i_minus_one_value = i - 1 >= 0 ? peak[i - 1] : 0;
    int old_i_plus_one_value = i + 1 < length ? peak[i + 1] : 0;

    update_peak(peak, segment, i, length);
    if(old_i_value != peak[i]) {
        update(tree, i, peak[i] - old_i_value, length);
    }
    if(i - 1 >= 0 && old_i_minus_one_value != peak[i - 1]) {
        update(tree, i - 1, peak[i - 1] - old_i_minus_one_value, length);
    }
    if(i + 1 < length && old_i_plus_one_value != peak[i + 1]) {
        update(tree, i + 1, peak[i + 1] - old_i_plus_one_value, length);
    }
}


// Functions to work with input data

void scan_segment(int segment[], size_t length, FILE *fp)
{
    for(int i = 0; i < length; i++) {
        fscanf(fp, "%d", &segment[i]);
    }
}


void scan_queries(int tree[], int segment[], int peak[], size_t length, FILE *fp)
{
    FILE *wp = fopen("output.txt", "w");
    int left, right, i, new_value;
    char input[BUFFER_SIZE];
    fscanf(fp, "%4s", input);
    while(strcmp(input, "END") != 0) {
        if(strcmp(input, "PEAK") == 0) {
            fscanf(fp, " %d %d", &left, &right);
            fprintf(wp, "%d\n", fenwick_tree_query(tree, left, right));
        } else if(strcmp(input, "UPD") == 0) {
            fscanf(fp, " %d %d", &i, &new_value);
            fenwick_tree_update(tree, segment, peak, i, new_value, length);
        } else {
            printf("\nInvalid command\n");
            return;
        }
    fscanf(fp, "%4s", input);
    }
    fclose(wp);
}


void clean_up(int tree[], int segment[], int peak[])
{
    free(tree);
    free(segment);
    free(peak);
}


int main()
{
    FILE *fp = fopen("input.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    int *tree = calloc(n, sizeof(int));

    int *segment = calloc(n, sizeof(int));
    scan_segment(segment, n, fp);
    
    int *peak = calloc(n, sizeof(int));
    make_peak(peak, segment, n);

    fenwick_tree_build(tree, peak, n);

    scan_queries(tree, segment, peak, n, fp);

    fclose(fp);
    clean_up(tree, segment, peak);
    return 0;
}

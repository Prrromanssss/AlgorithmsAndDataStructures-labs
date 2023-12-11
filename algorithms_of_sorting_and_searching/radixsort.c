#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FIELD_SIZE 256
#define NUMBER_OF_BYTES 4


union Int32 {
    int x;
    unsigned char bytes[NUMBER_OF_BYTES];
};


void scan_array(union Int32 arr[], size_t length)
{
    for(int i = 0; i < length; i++) {
        scanf("%d", &arr[i].x);
    }
}


void print_array(union Int32 arr[], size_t length)
{
    printf("\n\n");
    for(int i = 0; i < length; i++) {
        printf("%d ", arr[i].x);
    }
}


int key(unsigned char bytes[NUMBER_OF_BYTES], int q)
{
    if(q == NUMBER_OF_BYTES - 1) {
        return bytes[q] ^ 128;
    }
    return bytes[q];
}


void distribution_sort(union Int32 arr[], union Int32 *res, size_t length,
                       size_t key_length, int q,
                       int (*key)(unsigned char bytes[NUMBER_OF_BYTES], int q))
{
    int *count = calloc(key_length, sizeof(int));

    // number of entries for each key
    for(int j = 0; j < length; j++) {
       count[key(arr[j].bytes, q)]++;
    }

    // index for each key
    for(int i = 1; i < key_length; i++) {
        count[i] += count[i - 1];
    }

    // new sorted array
    for(int j = length - 1; j >= 0; j--) {
        int i = --count[key(arr[j].bytes, q)];
        res[i] = arr[j];
    }
    free(count);
}


void radix_sort(union Int32 arr[], size_t length,
                size_t key_length,
                int (*key)(unsigned char bytes[NUMBER_OF_BYTES], int q))
{
    union Int32 *res = calloc(length, sizeof(union Int32));
    for(int i = 0; i < NUMBER_OF_BYTES; i++) {
        distribution_sort(arr, res, length, key_length, i, key);
        memcpy(arr, res, length * sizeof(union Int32));
    }
    free(res);
}


int main() {
    int n;
    scanf("%d", &n);
    union Int32 nums[n];
    scan_array(nums, n);

    radix_sort(nums, n, FIELD_SIZE, key);

    print_array(nums, n);

    return 0;
}

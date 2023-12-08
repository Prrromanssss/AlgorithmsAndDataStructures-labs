#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


void scan_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}


void print_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}


void swap(void *base, unsigned int i, unsigned int j, size_t width)
{
    uint8_t *auxiliary_pointer_foк_swapping_left_right = malloc(width);
    uint8_t *left = base, *right = base;
    left += i * width;
    right += j * width;
    memcpy(auxiliary_pointer_foк_swapping_left_right, left, width);
    memcpy(left, right, width);
    memcpy(right, auxiliary_pointer_foк_swapping_left_right, width);
    free(auxiliary_pointer_foк_swapping_left_right);
}


void selection_sort(int arr[], int start, int end)
{
    for(int j = end; j > start; j--) {
        int k = j;
        for(int i = j - 1; i >= start; i--) {
            if(arr[k] < arr[i]) {
                k = i;
            }
        }
        swap(arr, j, k, sizeof(int));
    }
}


int partition(int arr[], int low, int high)
{
    int i = low;
    for(int j = low; j < high; j++) {
        if(arr[j] < arr[high]) {
            swap(arr, i, j, sizeof(int));
            i++;
        }
    }
    swap(arr, i, high, sizeof(int));
    return i;
}


void quick_sort(int arr[], int low, int high, int m)
{
    if(high - low + 1 < m) {
        selection_sort(arr, low, high);
        return;
    }
    while(low < high) {
        int q = partition(arr, low, high);
        if(q - low < high - q) {
            quick_sort(arr, low, q - 1, m);
            low = q + 1;
        } else {
            quick_sort(arr, q + 1, high, m);
            high = q - 1;
        }
    }
}


int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    scan_array(arr, n);

    quick_sort(arr, 0, n - 1, m);

    print_array(arr, n);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void revarray(void *base, size_t nel, size_t width)
{
    uint8_t *auxiliary_pointer_foк_swapping_left_right = malloc(width);
    uint8_t *left = base, *right = base;
    right += (nel - 1) * width;
    for(int i = 0; i < nel / 2; i++) {
        memcpy(auxiliary_pointer_foк_swapping_left_right, left,  width);
        memcpy(left, right, width);
        memcpy(right, auxiliary_pointer_foк_swapping_left_right, width);
        left += width;
        right -= width;
    }
    free(auxiliary_pointer_foк_swapping_left_right);
}

int scan_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    return *arr;
}

int main()
{
    size_t n;
    scanf("%zu", &n);
    int arr[n];
    *arr = scan_array(arr, n);
    revarray(arr, n, sizeof(int));
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}

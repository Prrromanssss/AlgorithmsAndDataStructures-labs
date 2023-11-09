#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scan_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    return *arr;
}

void revarray(void *base, size_t nel, size_t width)
{
    char *temp_pointer = malloc(width);
    for(int i = 0; i < nel / 2; i++) {
        char *left = base + i * width, *right = base + (nel - 1 - i) * width;
        memcpy(temp_pointer, left,  width);
        memcpy(left, right, width);
        memcpy(right, temp_pointer, width);
    }
    free(temp_pointer);
}

void print_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    *arr = scan_array(arr, n);
    revarray(arr, n, sizeof(int));
    print_array(arr, n);

}

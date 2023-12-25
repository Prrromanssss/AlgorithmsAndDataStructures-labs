#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


struct Task {
    int low, high;
};


struct Stack {
    struct Task *data;
    int capacity;
    int top;
};


void push(struct Stack *st, int low, int high)
{
    struct Task t = {low, high};
    if(st->top == st->capacity) {
        st->data = realloc(st->data, st->capacity * 2 * sizeof(struct Task));
        st->capacity *= 2;
    }
    st->data[st->top++] = t;
}


struct Task pop(struct Stack *st)
{
    return st->data[--st->top];
}


void swap(void *base, unsigned int i, unsigned int j, size_t width)
{
    uint8_t *auxiliary_pointer_for_swapping_left_right = malloc(width);
    uint8_t *left = base, *right = base;
    left += i * width;
    right += j * width;
    memcpy(auxiliary_pointer_for_swapping_left_right, left, width);
    memcpy(left, right, width);
    memcpy(right, auxiliary_pointer_for_swapping_left_right, width);
    free(auxiliary_pointer_for_swapping_left_right);
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


void quick_sort(struct Stack *st, int arr[], int low, int high)
{
    push(st, low, high);
    while(st->top) {
        struct Task last_task = pop(st);
        low = last_task.low;
        high = last_task.high;
        if(low >= high) {
            continue;
        }
        int q = partition(arr, low, high);
        push(st, low, q - 1);
        push(st, q + 1, high);
    }
}


void scan_array(int arr[], size_t length)
{
    for(int i = 0; i < length; i++) {
        scanf("%d", &arr[i]);
    }
}


void print_array(int arr[], size_t length)
{
    for(int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
}


void clean_up(struct Task *data, int *nums)
{
    free(data);
    free(nums);
}


int main()
{
    int n;
    scanf("%d", &n);
    int *nums = calloc(n, sizeof(int));
    scan_array(nums, n);

    struct Task *data = calloc(n, sizeof(struct Task));
    struct Stack st = {data, n, 0};

    quick_sort(&st, nums, 0, n - 1);

    print_array(nums, n);

    clean_up(data, nums);
    return 0;
}

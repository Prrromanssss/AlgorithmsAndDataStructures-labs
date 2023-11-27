#include <stdio.h>
#include <stdlib.h>


int* arr;


void swap(unsigned long i, unsigned long j)
{
    unsigned long tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}


int compare(unsigned long i, unsigned long j)
{
    if(arr[i] < arr[j]) return -1;
    if(arr[i] > arr[j]) return 1;
    return 0;
}


int scan_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    return *arr;
}


void print_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
}


unsigned long nearest_fib_digit(unsigned long x)
{
    if(x == 0) {
        return 0;
    }
    unsigned long fib0 = 1, fib1 = 1;
    while(fib1 < x) {
        fib1 += fib0;
        fib0 = fib1 - fib0;
    }
    return fib1 == x ? fib1 : fib0;
}


void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
    for(unsigned long d = nearest_fib_digit(nel); d > 0; d = nearest_fib_digit(d - 1)) {
        for(unsigned long i = d; i < nel; i++) {
            unsigned long j;
            for(j = i; j >= d && compare(j - d, j) >= 0; j -= d) {
                swap(j - d, j);
            }
        }
    }
}


int main()
{
    int n = 25;
    scanf("%d", &n);
    arr = (int*)malloc(n * sizeof(int));
    *arr = scan_array(arr, n);

    shellsort(n, compare, swap);

    print_array(arr, n);
    return 0;
}





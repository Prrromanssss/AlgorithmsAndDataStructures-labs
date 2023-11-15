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

void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
        for(unsigned long i = 0; i < nel; i++) {
            // left -> right
            for(unsigned long j = i + 1; j < nel; j++) {
                int res = compare(j, j - 1);
                if(res == -1) {
                    swap(j, j - 1);
                }
            }
            nel--;
            // right -> left
            for(unsigned long k = nel - 1; k > i; k--) {
                int res = compare(k, k - 1);
                if(res == -1) {
                    swap(k, k - 1);
                }
            }
        }
}

void print_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
}

int main()
{
    int n;
    scanf("%d", &n);

    arr = (int*)malloc(n * sizeof(int));
    *arr = scan_array(arr, n);

    bubblesort(n, compare, swap);

    print_array(arr, n);
    free(arr);
    return 0;
}





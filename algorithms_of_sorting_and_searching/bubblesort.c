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
        int left = 0;
        int right = nel - 1;
        while(left <= right) {
            // left -> right
            for(int j = left; j < right; j++) {
                int res = compare(j + 1, j);
                if(res == -1) {
                    swap(j + 1, j);
                }
            }
            right--;
            // right -> left
            for(int k = right; k > left; k--) {
                int res = compare(k, k - 1);
                if(res == -1) {
                    swap(k, k - 1);
                }
            }
            left++;
        }
}

void print_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
}

int main()
{
    int n = 1;
    scanf("%d", &n);

    arr = (int*)malloc(n * sizeof(int));
    *arr = scan_array(arr, n);

    bubblesort(n, compare, swap);

    print_array(arr, n);
    free(arr);
    return 0;
}





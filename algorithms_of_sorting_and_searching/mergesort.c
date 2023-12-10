#include <stdio.h>
#include <stdlib.h>


int* arr;


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
    printf("\n");
}


void insertion_sort(int arr[], int start, int end) {
    for(int i = start + 1; i < end + 1; i++) {
        int key = arr[i];
        int j = i - 1;

        while(j >= start && abs(arr[j]) > abs(key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void merge(int arr[], int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1];
    for(int i = 0; i < n1; i++) {
        left[i] = arr[start + i];
    }

    int right[n2];
    for(int i = 0; i < n2; i++) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0;
    int k = start;

    while(i != n1 && j != n2) {
        if(abs(left[i]) <= abs(right[j])) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i != n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j != n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}


void merge_sort(int arr[], int start, int end) {
    if(start < end) {
        int mid = (start + end) / 2;
        if((mid - start + 1) < 5) {
            insertion_sort(arr, start, mid);
        }
        else {
            merge_sort(arr, start, mid);
        }
        if((end - mid) < 5) {
            insertion_sort(arr, mid + 1, end);
        }
        else {
            merge_sort(arr, mid + 1, end);
        }
        merge(arr, start, mid, end);
    }
}


int main()
{
    int n = 10;
    scanf("%d", &n);

    arr = (int*)malloc(n * sizeof(int));
    *arr = scan_array(arr, n);

    merge_sort(arr, 0, n - 1);

    print_array(arr, n);
    free(arr);
    return 0;
}

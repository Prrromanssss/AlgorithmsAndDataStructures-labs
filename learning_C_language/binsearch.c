#include <stdio.h>
#define SIZE 10

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int aim = 6;

int scan_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    return *arr;
}

int compare(unsigned long i)
{
    if(arr[i] < aim) return -1;
    if(arr[i] > aim) return 1;
    return 0;
}


unsigned long binsearch(unsigned long nel, int(*compare)(unsigned long i))
{   
    int mid;
    int left = -1;
    int right = nel;
    while(right - left > 1) {
        mid = (right + left) / 2;
        int res = compare(mid);
        if(res == -1)
            left = mid;
        if(res == 0)
            return mid;
        if(res == 1)
            right = mid;
    }
    return nel;
}

int main()
{
    printf("%lu\n", binsearch(SIZE, compare));
    return 0;
}
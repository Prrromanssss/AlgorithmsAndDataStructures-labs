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
    int M;
    int L = -1;
    int R = nel;
    while(R - L > 1) {
        M = (R + L) / 2;
        int temp = compare(M);
        if(temp == -1)
            L = M;
        if(temp == 0)
            return M;
        if(temp == 1)
            R = M;
    }
    return nel;
}

int main()
{
    printf("%lu\n", binsearch(SIZE, compare));
    return 0;
}
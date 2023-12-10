#include <stdio.h>


int array_sum(int array[], int end)
{
    int sum = 0;
    for(int i = 0; i < end; i++) sum += array[i];
    return sum;
}


int found_max_sum_k(int array[], int length, int start)
{
    int prefix_sum = array_sum(array, start);
    int max_sum = prefix_sum;

    for(int i = start; i < length; i++) {
        prefix_sum -= array[i % start];
        prefix_sum += array[i];
        
        if(prefix_sum > max_sum) max_sum = prefix_sum;
        array[i % start] = array[i];
    }

    return max_sum;
}


int main()
{
    int n, k;
    scanf("%d", &n);
    int array[n];
    for(int i = 0; i < n; i++) scanf("%d", &array[i]);
    scanf("%d", &k);
    printf("%d", found_max_sum_k(array, n, k));
    return 0;
}

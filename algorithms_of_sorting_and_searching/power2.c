#include <stdio.h>


void increase_count_of_power2(int sum, int* count)
{
    if((sum > 0) && ((sum & (sum - 1)) == 0)) {
        *count += 1;
    }
}


int scan_array(int arr[], int n, int* count)
{
    int sum = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];

        // sums with length == 1
        increase_count_of_power2(arr[i], count);
    }

    // sum with length == n
    increase_count_of_power2(sum, count);

    return *arr;
}


void count_of_power2(int arr[], size_t length, int index, int sum, int *count)
{
    if(index == length) {
        increase_count_of_power2(sum, count);
        return;
    }
    count_of_power2(arr, length, index + 1, sum, count);
    count_of_power2(arr, length, index + 1, sum + arr[index], count);
}


int main()
{
    int n, count = 0;
    scanf("%d", &n);
    int arr[n];
    *arr = scan_array(arr, n, &count);
    count_of_power2(arr, n, 0, 0, &count);
    printf("%d\n", count);
    return 0;
}
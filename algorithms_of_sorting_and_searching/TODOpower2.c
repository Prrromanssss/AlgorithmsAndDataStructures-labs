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


void combination_with_repetition(int arr[],
                int index, int r, int start, int end, int* count, int sum)
{
    if (index == r) {
        increase_count_of_power2(sum, count);
        return;
    }

    for(int i = start + 1; i <= end + 1; i++) {
        combination_with_repetition(arr, index + 1, r, i, end, count, sum + arr[i - 1]);
    }
    return;
}


int count_of_power2(int arr[], int n, int *count)
{
    for(int r = 2; r < n; r++) {
        combination_with_repetition(arr, 0, r, 0, n-1, count, 0);
    }
    return *count;
}


int main()
{
    int n, count = 0;
    scanf("%d", &n);
    int arr[n];
    *arr = scan_array(arr, n, &count);
    printf("%d\n", count_of_power2(arr, n, &count));
    return 0;
}
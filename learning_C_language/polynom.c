#include <stdio.h>
#include <math.h>


long long calculate_px0(long long arr[], long long length, long long x0)
{
    long long px0 = arr[0];
    for(long long i = 0; i < length; i++) {
        px0 = px0 * x0 + arr[i + 1];
    }
    return px0;
}


long long calculate_pdx0(long long arr[], long long length, long long x0)
{
    for(long long i = 0; i < length; i++) {
        arr[i] = (length - i) * arr[i];
    }
    long long pdx0 = arr[0];
    for(long long i = 0; i < length - 1; i++) {
        pdx0 = pdx0 * x0 + arr[i + 1];
    }
    return pdx0;
}


int main()
{
    long long n, x0;
    scanf("%lld %lld", &n, &x0);
    long long arr[n + 1];

    // scanning array of elements
    for(long long i = 0; i <= n; i++) scanf("%lld", &arr[i]);

    long long px0 = calculate_px0(arr, n, x0);
    long long pdx0 = calculate_pdx0(arr, n, x0);

    printf("%lld %lld", px0, pdx0);
    return 0;
}

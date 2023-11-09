#include <stdio.h>

int main() {
    int n, x0;
    int px0 = 0, pdx0 = 0;
    scanf("%d %d", &n, &x0);
    int arr[n + 1];
    for(int i = 0; i <= n; i++) {
        scanf("%d", &arr[i]);
        px0 += arr[i];
        if(i != n) px0 *= x0;
    }
    for(int i = 0; i < n; i++) {
        pdx0 += (n - i) * arr[i];
        if(i != n - 1) pdx0 *= x0;
    }

    printf("Pn(x0) = %d, P`n(x0) = %d", px0, pdx0);
    return 0;
}
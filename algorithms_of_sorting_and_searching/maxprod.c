#include <stdint.h>
#include <stdio.h>


typedef struct Fraction {
    double numer, denom;
} fract;


void scan_fractions(fract arr[], size_t length)
{
    for(int i = 0; i < length; i++) {
        scanf("%lf %*c %lf", &arr[i].numer, &arr[i].denom);
    }
}


void kadane(fract arr[], size_t length, int *left, int *right)
{
    double maxprod = arr[0].numer / arr[0].denom;
    int start = 0;
    double prod = 1.0;
    int i = 0;
    while(i < length) {
        prod *= arr[i].numer / arr[i].denom;
        if(prod > maxprod) {
            maxprod = prod;
            *left = start;
            *right = i;
        }
        i++;
        if(prod < 1) {
            prod = 1.0;
            start = i;
        }
    }
}


int main()
{
    int left = 0, right = 0;
    int n;
    scanf("%d", &n);
    fract arr[n];
    scan_fractions(arr, n);
    kadane(arr, n, &left, &right);
    printf("%d %d\n", left, right);
    return 0;
}

#include <stdio.h>


unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    unsigned long long bin[64];
    int i = 0;
    while (b) {
        bin[i] = b % 2;
        b /= 2;
        i++;
    }
    i--;
    unsigned long long res = (a % m) * (bin[i] % m);
    for(int k = i - 1; k >= 0; k--) {
        res = (res % m) * 2;
        res = ((res % m) + ((a % m) * (bin[k] % m)) % m) % m;
    }
    return res;
}


int main()
{
    unsigned long long a, b, m;
    scanf("%lld %lld %lld", &a, &b, &m);
    printf("%lld", mulmod(a, b, m));
    return 0;
}

#include <stdio.h>

int dec2bin(int num)
{
    int bin = 0, k = 1;
    while (num) {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }
    return bin;
}

int get_len_of_number(long long num)
{
    int len = 1;
    while(num / 10) {
        len++;
        num /= 10;
    }
    return len;
}
 

int mulmod(int a, int b, int m)
{
    long long bin_b = dec2bin(b);
    int len_bin_b = get_len_of_number(bin_b);
    int res = 0;
    int bArray[len_bin_b];
    long long new_b = bin_b;
    int j = len_bin_b - 1;
    while(new_b != 0) {
        bArray[j] = new_b % 10;
        new_b /= 10;
        j--;
    }
    for(int i = 0; i < len_bin_b; i++) {
        res = (res % m + ((a % m) * (bArray[i] % m) % m)) % m;
        if (i != len_bin_b - 1) res = ((res % m) * (2 % m)) % m;
    }
    return res % m;
}

int main() {
    int a, b, m;
    scanf("%d %d %d", &a, &b, &m);
    printf("%d", mulmod(a, b, m));
    return 0;
}
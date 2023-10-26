#include <stdio.h>

void sieve_of_Eratosthenes(int *prime, int n) {
    for(int i = 2; i < n + 1; i++) {
        if(!prime[i]) {
            continue;
        }
        for(int j = i * i; j < n + 1; j += i) {
            prime[j] = 0;
        }
    }
}


int main() {
    int n;
    scanf("%d", &n);
    int prime[n + 1];
    prime[0] = 0;
    prime[1] = 0;
    for(int i = 2; i < n + 1; i++) {
        prime[i] = 1;
    }
    sieve_of_Eratosthenes(prime, n);
    for(int i = n; i > 0; i--) {
        if(n % i == 0 && prime[i]) {
            printf("%d", i);
            break;
        }
    }
    return 0;
}
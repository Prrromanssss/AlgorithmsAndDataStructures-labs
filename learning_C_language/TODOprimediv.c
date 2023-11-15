#include <stdio.h>
#include <stdlib.h>


long* prime;


long input(long n)
{
    // scanf("%ld", &n);
    return n > 0 ? n : -n;
}


void init_sieve_of_Eratosthenes(long prime[], long n)
{
    prime[0] = 0;
    prime[1] = 0;
    for(long i = 2; i < n + 1; i++) {
        prime[i] = 1;

    }
}


void fill_sieve_of_Eratosthenes(long prime[], long n)
{
    for(long i = 2; i < n + 1; i++) {
        if(!prime[i]) {
            continue;
        }
        for(long j = i * i; j < n + 1; j += i) {
            prime[j] = 0;
        }
    }
}


void print_largest_prime_factor(long prime[], long n)
{
    for(long i = n; i > 0; i--) {
        if(n % i == 0 && prime[i]) {
            printf("%ld", i);
            return;
        }
    }
}


int main()
{
    long n = -2147483648;
    n = input(n);

    prime = (long*)malloc(sizeof(long) * (n + 1));
    init_sieve_of_Eratosthenes(prime, n);
    fill_sieve_of_Eratosthenes(prime, n);
    print_largest_prime_factor(prime, n);
    free(prime);
    return 0;
}
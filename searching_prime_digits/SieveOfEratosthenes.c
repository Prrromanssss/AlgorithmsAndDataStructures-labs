#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* prime;

void SieveOfEratosthenes(int prime[], int length)
{
    for(int i = 0; i < length; i++) {
        prime[i] = 1;
    }

    for(int p = 2; p * p < length; p++) {
        if(!prime[p])
            continue;
        for(int i = p * p; i < length; i += p) {
            prime[i] = 0;
        }
    }
}


void ListPrimes(int prime[], int length)
{
    for(int i = 2; i < length; i++)
        if(prime[i])
            printf("%d\n", i);
}


int main()
{
    int n = 550000000; // -> 8.6 sec
    // scanf("%d", &n);
    prime = (int*)malloc(sizeof(int) * n);

    clock_t t;
    t = clock();

    SieveOfEratosthenes(prime, n);
    // ListPrimes(prime, n);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("SieveOfEratosthenes() took %.2f seconds to execute \n", time_taken); 

    free(prime);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* prime;

void SieveOfEratosthenes(int prime[], int length)
{
    for(int i = 0; i < length; i++) {
        prime[i] = 1;
    }

    for (int i = 1; i + i + 2 * i * i < length; i++) {
        for (int j = i; i + j + 2 * i * j < length; j++) {
            prime[i + j + 2 * i * j] = 0;
        }
    }
}


void ListPrimes(int prime[], int length)
{
    printf("%d\n", 2);
    for(int i = 2; i < length; i++)
        if(prime[i]) {
            int p = i * 2 + 1;
            if(p >= length) break;
            printf("%d\n", p);
        }
}


int main()
{
    int n = 550000000; // -> 6.8 sec
    // scanf("%d", &n);
    int length = (n + 1) / 2;
    prime = (int*)malloc(sizeof(int) * length);

    clock_t t;
    t = clock();

    SieveOfEratosthenes(prime, length);
    // ListPrimes(prime, length);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("SieveOfEratosthenes() took %.2f seconds to execute \n", time_taken); 

    free(prime);
    return 0;
}

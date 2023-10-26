#include <stdio.h>


int fibonacci_number(int n)
{
    int number = 1;
    int fib0 = 1, fib1 = 1;
    if(n != 0) {
        while(fib1 != n) {
            fib1 += fib0;
            fib0 = fib1 - fib0;
            number += 1;
        }
    } else {
        number = 1;
    }
    return number;
}


int main()
{
    int x;
    scanf("%d", &x);
    int array[x];
    int i = 0;
    while(x > 0) {
        int fib1 = 0, fib2 = 1;
        while(fib2 < x) {
            fib2 += fib1;
            fib1 = fib2 - fib1;
        }
        array[i] = fib2 == x ? fib2 : fib1;
        x -= fib2 == x ? fib2 : fib1;
        i++;
    }
    int one_in_fns[i];
    for(int j = 0; j < i; j++) {
        one_in_fns[j] = fibonacci_number(array[j]);
    }
    int another_j = 0;
    for(int j = one_in_fns[0]; j > 0; j--) {
        if(one_in_fns[another_j] == j) {
            printf("%d", 1);
            another_j++;
        }
        else printf("%d", 0);
    }
    return 0;
}
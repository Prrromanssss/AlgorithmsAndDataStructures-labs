#include <stdio.h>


typedef unsigned long long big_size;


int fibonacci_number(big_size n)
{
    int number = 1;
    big_size fib0 = 1, fib1 = 1;
    if(n == 0) return 1;
    while(fib1 != n) {
        fib1 += fib0;
        fib0 = fib1 - fib0;
        number += 1;
    }
    return number;
}


int amount_units_by_zeckendorf_sum(big_size x)
{
    int i = 0;
    while(x > 0) {
        big_size fib0 = 1, fib1 = 1;
        while(fib1 < x) {
            fib1 += fib0;
            fib0 = fib1 - fib0;
        }
        x -= fib1 == x ? fib1 : fib0;
        i++;
    }
    return i;
}

void from_zec_sum_to_fib_number(big_size x, int res[], int length)
{
    int j = 0;
    while(x > 0) {
        big_size fib0 = 1, fib1 = 1;
        while(fib1 < x) {
            fib1 += fib0;
            fib0 = fib1 - fib0;
        }
        if(j < length) {
            res[j] = fibonacci_number(fib1 == x ? fib1 : fib0);
            j++;
        }
        x -= fib1 == x ? fib1 : fib0;
    }
}


void print_digit_in_fns(int units_in_fns[], size_t length)
{
    int units_counter = 0;
    for(int j = units_in_fns[0]; j > 0; j--) {
        if(units_counter < length && units_in_fns[units_counter] == j) {
            printf("%d", 1);
            units_counter++;
        }
        else printf("%d", 0);
    }
}


int main()
{
    big_size x;
    scanf("%lld", &x);
    if(x == 0) {
        printf("0");
        return 0;
    }

    // count amount of units in fns using zeckendorf sum
    int amount_of_zeckendorf_sum = amount_units_by_zeckendorf_sum(x);
    int units_in_fns[amount_of_zeckendorf_sum];

    // converting number from zeckendorf sum to its fibonacci number
    from_zec_sum_to_fib_number(x, units_in_fns, amount_of_zeckendorf_sum);

    // built given digit in fns
    print_digit_in_fns(units_in_fns, amount_of_zeckendorf_sum);
    return 0;
}
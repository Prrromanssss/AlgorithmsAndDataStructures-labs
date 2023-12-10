#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


long get_fib_number(long n)
{
    return (long)round((pow(((1 + sqrt(5)) / 2), n) - pow(((1 - sqrt(5)) / 2), n)) / sqrt(5));
}


void init_arrays(char *fib1, char *fib2, char *temp, size_t length)
{
    for(int i = 0; i < length; i++) {
        fib1[i] = '\0';
        fib2[i] = '\0';
        temp[i] = '\0';
    }
}


char *fibstr(int n)
{
    if(n <= 0) {
        return "";
    }
    long max_size = get_fib_number(n);

    char *fib1 = (char *)malloc(sizeof(char) * (max_size + 1));
    char *fib2 = (char *)malloc(sizeof(char) * (max_size + 1));
    char *temp = (char *)malloc(sizeof(char) * (max_size + 1));

    init_arrays(fib1, fib2, temp, max_size + 1);

    fib1[0] = 'a';
    fib2[0] = 'b';
    for(int i = 0; i < n - 2; i++) {
        strcpy(temp, fib1);
        strcpy(fib1, fib2);
        strcpy(fib2, strcat(temp, fib2));
    }
    free(temp);

    if(n > 1) {
        free(fib1);
        return fib2;
    } else {
        free(fib2);
        return fib1;
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    char *res = fibstr(n);
    printf("%s\n", res);
    if(strcmp(res, "") != 0) {
        free(res);
    }
    return 0;
}

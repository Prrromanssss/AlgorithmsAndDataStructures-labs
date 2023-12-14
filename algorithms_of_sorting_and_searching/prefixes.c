#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct StringWithLength {
    char *data;
    int length;
} str_l;


void init_strings(str_l *str, char argv_1[])
{
    str->data = calloc(strlen(argv_1) + 1, sizeof(char));
    strncpy(str->data, argv_1, strlen(argv_1) * sizeof(char));
    str->length = strlen(argv_1);
}


void prefix(str_l str, int pi[])
{
    pi[0] = 0;
    int t = 0;
    for(int i = 1; i < str.length; i++) {
        while(t > 0 && str.data[t] != str.data[i]) {
            t = pi[t - 1];
        }
        if(str.data[t] == str.data[i]) {
            t++;
        }
        pi[i] = t;
    }
}


int gcd(int a, int b)
{
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}


void find_periodic_prefixes(int pi[], size_t length)
{
    for(int i = 0; i < length; i++) {
        if(i && i + 1 - pi[i] == 1) {
            printf("%d %d\n", i + 1, i + 1);
        } else if(pi[i] && gcd(pi[i], i + 1) != 1 && ((i + 1) / 2) <= pi[i]) {
            printf("%d %d\n", i + 1, (i + 1) / gcd(pi[i], i + 1));
        }
    }
}


int main(int argc, char **argv)
{
    if(argc != 2) {
        printf("Usage: kmpall <string>\n");
        return 0;
    }
    str_l str;
    init_strings(&str, argv[1]);

    int pi[str.length];

    prefix(str, pi);

    find_periodic_prefixes(pi, str.length);

    free(str.data);
    return 0;
}

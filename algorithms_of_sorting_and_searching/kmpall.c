#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct StringWithLength {
    char *data;
    int length;
} str_l;


void init_strings(str_l *substr, str_l *str,
                  char argv_1[], char argv_2[])
{
    substr->data = calloc(strlen(argv_1) + 1, sizeof(char));
    strncpy(substr->data, argv_1, strlen(argv_1) * sizeof(char));
    substr->length = strlen(argv_1);

    str->data = calloc(strlen(argv_2) + 1, sizeof(char));
    strncpy(str->data, argv_2, strlen(argv_2) * sizeof(char));
    str->length = strlen(argv_2);
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


void kmp_subst(str_l subst, str_l str)
{
    int pi[subst.length];
    prefix(subst, pi);

    int q = 0, k = 0;
    while(k < str.length) {
        while(q > 0 && subst.data[q] != str.data[k]) {
            q = pi[q - 1];
        }
        if(subst.data[q] == str.data[k]) {
            q++;
        }
        if(q == subst.length) {
            printf("%d\n", k - subst.length + 1);
        }
        k++;
    }
}


int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Usage: kmpall <substring(S)> <string(T)>\n");
        return 0;
    }
    str_l substr, str;
    init_strings(&substr, &str, argv[1], argv[2]);

    kmp_subst(substr, str);

    free(str.data);
    free(substr.data);
    return 0;
}

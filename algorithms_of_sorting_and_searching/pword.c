#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct StringWithLength {
    char *data;
    int length;
} str_l;


void init_strings(str_l *str_s, str_l *str_t,
                  char argv_1[], char argv_2[])
{
    str_s->data = calloc(strlen(argv_1) + 1, sizeof(char));
    strncpy(str_s->data, argv_1, strlen(argv_1) * sizeof(char));
    str_s->length = strlen(argv_1);

    str_t->data = calloc(strlen(argv_2) + 1, sizeof(char));
    strncpy(str_t->data, argv_2, strlen(argv_2) * sizeof(char));
    str_t->length = strlen(argv_2);
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


void pword(str_l str_s, str_l str_t)
{
    int pi[str_s.length];
    prefix(str_s, pi);

    int q = 0, k = 0;
    while(k < str_t.length) {
        while(q > 0 && str_s.data[q] != str_t.data[k]) {
            q = pi[q - 1];
        }
        if(str_s.data[q] == str_t.data[k]) {
            q++;
        }
        if(q == 0) {
            printf("no\n");
            return;
        }
        k++;
    }
    printf("yes\n");
}


int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Usage: pword <string(S)> <string(T)>\n");
        return 0;
    }
    str_l str_s, str_t;
    init_strings(&str_s, &str_t, argv[1], argv[2]);

    pword(str_s, str_t);

    free(str_s.data);
    free(str_t.data);

    return 0;
}

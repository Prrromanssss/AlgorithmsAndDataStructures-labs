#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 256


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


int max(int a, int b)
{
    return a > b ? a : b;
}


void delta1(str_l s, int size, int d1[])
{
    for(int a = 0; a < size; a++) {
        d1[a] = s.length;
    }
    for(int j = 0; j < s.length - 1; j++) {
        d1[s.data[j]] = s.length - j - 1;
    }
}


void suffix(str_l s, int delt[])
{
    int t = s.length - 1;
    delt[s.length - 1] = t;
    for(int i = s.length - 2; i >= 0; i--) {
        while(t < s.length - 1 && s.data[t] != s.data[i]) {
            t = delt[t + 1];
        }
        if(s.data[t] == s.data[i]) {
            t--;
        }
        delt[i] = t;
    }

}


void delta2(str_l s, int d2[])
{
    int delt[s.length];
    suffix(s, delt);
    int t = delt[0];
    for(int i = 0; i < s.length; i++) {
        while(t < i) {
            t = delt[t + 1];
        }
        d2[i] = -i + t + s.length;
    }
    for(int i = 0; i < s.length - 1; i++) {
        int t = i;
        while(t < s.length - 1) {
            t = delt[t + 1];
            if(s.data[i] != s.data[t]) {
                d2[t] = -(i + 1) + s.length;
            }
        }
    }
}


void bm_subst(str_l s, int size, str_l t)
{
    int d1[size];
    delta1(s, size, d1);
    int d2[s.length];
    delta2(s, d2);
    int k = s.length - 1;
    int i;
    while(k < t.length) {
        i = s.length - 1;
        while(t.data[k] == s.data[i]) {
            if(i == 0) {
                printf("%d\n", k);
                break;
            }
            i--;
            k--;
        }
        k = k + max(d1[t.data[k]], d2[i]);
    }    
}


int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Usage: bmall <substring(S)> <string(T)>\n");
        return 0;
    }
    str_l substr, str;
    init_strings(&substr, &str, argv[1], argv[2]);

    bm_subst(substr, SIZE, str);

    free(str.data);
    free(substr.data);
    return 0;
}

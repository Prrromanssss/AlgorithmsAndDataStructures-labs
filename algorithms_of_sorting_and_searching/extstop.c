#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 256


typedef struct StringWithLength {
    char *data;
    int length;
} str_l;


int max(int a, int b)
{
    return a > b ? a : b;
}


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


void delta1(str_l s, int size, int **d1)
{
    for(int i = 0; i < s.length; i++) {
        for(int j = 0; j < size; j++) {
            d1[i][j] = s.length;
        }
    }
    d1[0][s.data[0]] = s.length - 1;
    for(int i = 1; i < s.length; ++i) {
        memcpy(d1[i], d1[i - 1], size * sizeof(int));
        d1[i][s.data[i]] = s.length - i - 1;
    }
}


void del_2d_array(int **arr, size_t length)
{
    for(int i = 0; i < length; i++) {
        free(arr[i]);
    }
    free(arr);
}


int bm_subst(str_l subst, int size, str_l source)
{
    int **d1 = calloc(subst.length, sizeof(int *));
    for(int i = 0; i < subst.length; i++) {
        d1[i] = calloc(size, sizeof(int));
    }

    delta1(subst, size, d1);
    int k = subst.length - 1;
    int i;
    while(k < source.length) {
        i = subst.length - 1;
        while(source.data[k] == subst.data[i]) {
            if(i == 0) {
                del_2d_array(d1, subst.length);
                return k;
            }
            i--;
            k--;
        }
        k = k + max(d1[i][source.data[k]], subst.length - i);
    }
    del_2d_array(d1, subst.length);
    return source.length;
}


int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Usage: extstop <substring(S)> <string(T)>\n");
        return 1;
    }
    str_l substr, source;
    init_strings(&substr, &source, argv[1], argv[2]);

    printf("%d\n", bm_subst(substr, SIZE, source));

    free(source.data);
    free(substr.data);
    return 0;
}

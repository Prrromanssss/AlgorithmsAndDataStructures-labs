#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


#define BUFFER_SIZE 1000001


char *distribution_sort(char arr[], size_t length, size_t key_length)
{
    int *count = calloc(key_length, sizeof(int));

    // number of entries for each key
    for(int j = 0; j < length; j++) {
       count[arr[j] - 'a']++;
    }

    // index for each key
    for(int i = 1; i < key_length; i++) {
        count[i] += count[i - 1];
    }

    // new sorted string
    char *res = calloc(length + 1, sizeof(char));
    for(int j = length - 1; j >= 0; j--) {
        int i = count[arr[j] - 'a'] - 1;
        count[arr[j] - 'a'] = i;
        res[i] = arr[j];
    }
    res[length] = '\0';
    free(count);
    return res;
}


void strip(char str[])
{
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}


int main()
{
    
    char str[BUFFER_SIZE];
    fgets(str, BUFFER_SIZE, stdin);
    strip(str);
    char *res = distribution_sort(str, strlen(str), 26);

    printf("%s\n", res);

    free(res);
    return 0;
}
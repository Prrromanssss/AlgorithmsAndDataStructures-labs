#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 1001


char *concat(char **s, int n)
{
    int length = 0;
    for(int i = 0; i < n; i++) {
        length += strlen(s[i]);
    }
    char *new_string = (char *)malloc(sizeof(char) * (length + 1));
    length = 0;
    for(int i = 0; i < n; i++) {
        memcpy(new_string + length, s[i], strlen(s[i]) + 1);
        length += strlen(s[i]);
    }
    new_string[length] = '\0';
    return new_string;
}

void scan_strings(char **words, size_t length)
{
    for(int i = 0; i < length; i++) {
        char word[BUFFER_SIZE];
        scanf("%s", word);
        words[i] = (char *)malloc(strlen(word) + 1);
        strcpy(words[i], word);
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    if(n <= 0) {
        printf("\n");
        return 0;
    }
    char **words = (char **)malloc(sizeof(char *) * n);
    scan_strings(words, n);

    char *concat_string = concat(words, n);

    printf("%s\n", concat_string);

    // Clearing the memory
    for(int i = 0; i < n; i++) free(words[i]);
    free(words);
    free(concat_string);

    return 0;
}

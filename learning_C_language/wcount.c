#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 1000000


int wcount(char *str)
{
    bool is_string_without_space = false;
    int count = 0;

    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(str[i] != '\n' && str[i] != ' ' && str[i] != '\0' && !is_string_without_space) {
            is_string_without_space = true;
        }
        if((str[i] == '\n' || str[i] == ' ' || str[i] == '\0') && is_string_without_space) {
            count++;
            is_string_without_space = false;
        }
        if(str[i] == '\n' || str[i] == '\0') {
            break;
        }
    }
    return count;
}


int main()
{
    char string[BUFFER_SIZE];
    fgets(string, BUFFER_SIZE, stdin);
    printf("%d", wcount(string));
    return 0;
}
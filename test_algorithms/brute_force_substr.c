#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000


void slice(const char *src, char *dest, size_t start, size_t end)
{
    strncpy(dest, src + start, end - start);
}


int BruteForceSubst(char s[], char t[])
{
    int k = 0;
    while(k < strlen(t) - strlen(s) + 1) {
        char temp[strlen(s) + 1];
        slice(t, temp, k, k + strlen(s));
        if(strcmp(temp, s) == 0) {
            return k;
        }
        k++;
    }
    return strlen(t);
}



int main()
{
    char s[] = "hello";
    char res[] = "ell";

    printf("%d", BruteForceSubst(res, s));

}
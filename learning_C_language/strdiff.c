#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 1000000
#define SIZE_OF_CHAR_IN_BITS sizeof(char) * 8


int cmp_letters(uint8_t, uint8_t);


int cmp_letters(uint8_t let1, uint8_t let2)
{
    int bin1[SIZE_OF_CHAR_IN_BITS], bin2[SIZE_OF_CHAR_IN_BITS];
    for(int i = SIZE_OF_CHAR_IN_BITS - 1; i >= 0; i--) {
        bin1[i] = let1 % 2;
        bin2[i] = let2 % 2;
        let1 /= 2;
        let2 /= 2;
    }

    for(int i = SIZE_OF_CHAR_IN_BITS - 1; i >= 0; i--) {
        if(bin1[i] != bin2[i]) {
            return SIZE_OF_CHAR_IN_BITS - 1 - i;
        }
    }
    return -1;
}


int strdiff(char *a, char *b)
{
    int diff = 0;
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(a[i] == '\n' || (a[i] == '\0' && b[i] == '\0')) {
            break;
        }
        int res = cmp_letters(a[i], b[i]);
        if(res == -1) {
            diff += SIZE_OF_CHAR_IN_BITS;
        }
        else {
            return diff + res;
        }
    }
    return -1;
}


int main()
{
    char string1[BUFFER_SIZE], string2[BUFFER_SIZE];

    fgets(string1, BUFFER_SIZE, stdin);
    fgets(string2, BUFFER_SIZE, stdin);
    printf("%d\n", strdiff(string1, string2));

    return 0;
}

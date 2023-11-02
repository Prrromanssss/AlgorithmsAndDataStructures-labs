#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void revarray(void *base, size_t nel, size_t width)
{
    char *temp_pointer = malloc(width);
    for(int i = 0; i < nel / 2; i++) {
        char *left = base + i * width, *right = base + (nel - 1 - i) * width;
        memcpy(temp_pointer, left,  width);
        memcpy(left, right, width);
        memcpy(right, temp_pointer, width);
    }
    free(temp_pointer);

}
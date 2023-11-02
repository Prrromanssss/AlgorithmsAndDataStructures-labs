#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxarray(void *base, size_t nel, size_t width,
        int(*compare)(void *a, void *b))
{
    char *p_max_elem = malloc(width);
    int max_index = 0;
    memcpy(p_max_elem, base, width);
    for(int i = 0; i < nel; i++) {
        char *elem = base + i * width;
        int res = compare(elem, p_max_elem);
        if(res > 0) {
            max_index = i;
            memcpy(p_max_elem, elem, width);
        }
    }

    free(p_max_elem);
    return max_index;
}


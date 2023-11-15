#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int maxarray(void *base, size_t nel, size_t width,
        int(*compare)(void *a, void *b))
{
    uint8_t *p_max_elem = malloc(width);
    uint8_t *elem = base;
    int max_index = 0;
    memcpy(p_max_elem, base, width);
    for(int i = 1; i < nel; i++) {
        elem += width;
        int res = compare(elem, p_max_elem);
        if(res > 0) {
            max_index = i;
            memcpy(p_max_elem, elem, width);
        }
    }
    free(p_max_elem);
    return max_index;
}

int scan_array(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    return *arr;
}

int compare(void *a, void *b)
{
    if ((*(unsigned char*)a) > (*(unsigned char*)b))
		return 1;
	if ((*(unsigned char*)a) < (*(unsigned char*)b))
		return -1;
	return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    *arr = scan_array(arr, n);
    printf("%d", maxarray(arr, n, sizeof(int), compare));
    return 0;
}

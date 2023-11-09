#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    *arr = scan_array(arr, n);
    printf("%d", maxarray(arr, n, sizeof(int), compare));

    return 0;
}

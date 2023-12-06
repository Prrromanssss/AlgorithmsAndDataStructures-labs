#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define BUFFER_SIZE 10000
#define SORT_KEY 'a'


void scan_array_of_strings(char words[][BUFFER_SIZE], size_t length)
{
    for(int i = 0; i < length; i++) {
        scanf("%s", words[i]);
    }
}


void print_array_of_strings(char words[][BUFFER_SIZE], size_t length)
{
    for(int i = 0; i < length; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
}


int count_sort_key(char s[])
{
    int count = 0;
    for(int i = 0; i < strlen(s); i++) {
        if(s[i] == SORT_KEY) {
            count++;
        }
    }
    return count;
}


int compare(const void *a, const void *b)
{
    char *s1 = (char *)a;
    char *s2 = (char *)b;
    int count_sort_key_s1 = count_sort_key(s1);
    int count_sort_key_s2 = count_sort_key(s2);
    if(count_sort_key_s1 > count_sort_key_s2) {
        return count_sort_key_s1;
    } else if(count_sort_key_s1 < count_sort_key_s2) {
        return -count_sort_key_s2;
    }
    return 0;
}


int left(int i)
{
    return 2 * i + 1;
}


int right(int i)
{
    return 2 * i + 2;
}


void swap(void *base, unsigned int i, unsigned int j, size_t width)
{
    uint8_t *temp_pointer = malloc(width);
    uint8_t *left = base, *right = base;
    left += i * width;
    right += j * width;
    memcpy(temp_pointer, left, width);
    memcpy(left, right, width);
    memcpy(right, temp_pointer, width);
    free(temp_pointer);
}


void max_heapify(void *base, int i, int heap_size, size_t width,
            int (*compare)(const void *a, const void *b))
{
    uint8_t *read_pointer = base;
    int l = left(i);
    int r = right(i);
    int largest = -1;
    if(l < heap_size && compare(read_pointer + l * width, read_pointer + i * width) > 0) {
        largest = l;
    } else {
        largest = i;
    }
    if(r < heap_size && compare(read_pointer + r * width, read_pointer + largest * width) > 0) {
        largest = r;
    }
    if(largest != i) {
		swap(base, i, largest, width);
		max_heapify(base, largest, heap_size, width, compare);
	}
}


void build_max_heap(void *base, size_t length, size_t width,
            int (*compare)(const void *a, const void *b))
{
    for(int i = length / 2 - 1; i >= 0; i--) {
        max_heapify(base, i, length, width, compare);
    }
}


void hsort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b))
{
    build_max_heap(base, nel, width, compare);
    for(int i = nel - 1; i > 0; i--) {
        swap(base, 0, i, width);
        max_heapify(base, 0, i, width, compare);
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    char words[n][BUFFER_SIZE];

    scan_array_of_strings(words, n);

    hsort(*words, n, BUFFER_SIZE, compare);

    print_array_of_strings(words, n);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define NUMBER_OF_RADIX 3


enum NUMBER_OF_FIELDS {
    number_of_days = 31,
    number_of_months = 12,
    number_of_years = 61,
};


struct Date {
    int Day, Month, Year;
};


void distribution_sort(struct Date arr[], struct Date *res, size_t length,
                       size_t key_length, int q,
                       int (*key)(struct Date date, int q))
{
    int *count = calloc(key_length, sizeof(int));

    // number of entries for each key
    for(int j = 0; j < length; j++) {
       count[key(arr[j], q)]++;
    }

    // index for each key
    for(int i = 1; i < key_length; i++) {
        count[i] += count[i - 1];
    }

    // new sorted array
    for(int j = length - 1; j >= 0; j--) {
        int i = --count[key(arr[j], q)];
        res[i] = arr[j];
    }
    free(count);
}


int key(struct Date date, int q)
{
    if(q == 2) {
        return date.Day - 1;
    } else if(q == 1) {
        return date.Month - 1;
    } else if(q == 0) {
        return date.Year - 1970;
    }
    return -1;
}


int key_length(int q)
{
    if(q == 2) {
        return number_of_days;
    } else if(q == 1) {
        return number_of_months;
    } else if(q == 0) {
        return number_of_years;
    }
    return -1;
}


void date_sort(struct Date arr[], int q, size_t length,
                int (*key)(struct Date date, int q),
                int (*key_length)(int q))
{
    struct Date *res = calloc(length, sizeof(struct Date));
    for(int i = q; i >= 0; i--) {
        distribution_sort(arr, res, length, key_length(i), i, key);
        memcpy(arr, res, length * sizeof(struct Date));
    }
    free(res);
}


void print_date(struct Date arr[], size_t length)
{   
    printf("\n\n");
    for(int i = 0; i < length; i++) {
        printf("%04d %02d %02d\n", arr[i].Year, arr[i].Month, arr[i].Day);
    }
}


void scan_date(struct Date arr[], size_t length)
{
    for(int i = 0; i < length; i++) {
        scanf("%d %d %d", &arr[i].Year, &arr[i].Month, &arr[i].Day);
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    struct Date arr[n];
    scan_date(arr, n);

    date_sort(arr, NUMBER_OF_RADIX - 1, n, key, key_length);

    print_date(arr, n);
    return 0;
}

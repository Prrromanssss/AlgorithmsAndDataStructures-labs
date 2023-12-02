#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define BUFFER_SIZE 100000


int wcount(char *str)
{
    bool is_string_without_space = false;
    int count = 0;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (str[i] != '\n' && str[i] != ' ' && str[i] != '\0' && !is_string_without_space) {
            is_string_without_space = true;
        }
        if ((str[i] == '\n' || str[i] == ' ' || str[i] == '\0') && is_string_without_space) {
            count++;
            is_string_without_space = false;
        }
        if (str[i] == '\n' || str[i] == '\0') {
            break;
        }
    }
    return count;
}


int make_count_array(char *src, size_t length, int count_array[])
{
    bool is_word = false;
    int j = 0;
    int count_of_word = 0;
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(src[i] == ' ' && !is_word) {
            continue;
        } else if(src[i] == '\n' || src[i] == '\0') {
            if(j < length) {
                count_array[j] = count_of_word;
            }
            break;
        } else if (src[i] == ' ' && is_word) {
            count_array[j] = count_of_word;
            j++;
            count_of_word = 0;
            is_word = false;
        } else {
            count_of_word++;
            is_word = true;
        }
    }

    return *count_array;
}


char make_src_without_spaces(char *src, size_t length_of_raw_src, char raw_src[])
{
    bool is_word = false;
    int j = 0;
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(src[i] == ' ' && !is_word) {
            continue;
        } else if(src[i] == '\n' || src[i] == '\0') {
            break;
        } else if (src[i] == ' ' && is_word) {
            is_word = false;
        } else {
            raw_src[j] = src[i];
            j++;
            is_word = true;
        }
    }
    return *raw_src;
}


size_t length_of_dest(char *src)
{
    bool is_word = false;
    size_t count = 0;
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(src[i] == ' ' && !is_word) {
            continue;
        } else if(src[i] == '\n' || src[i] == '\0') {
            count++;
            break;
        } else if (src[i] == ' ' && is_word) {
            count++;
            is_word = false;
        } else {
            count++;
            is_word = true;
        }
    }
    return count;
}


void csort(char *src, char *dest)
{
    size_t length = wcount(src);

    // Get length of the dest array
    size_t length_of_dest_array = length_of_dest(src);

    // Get count array(i. e. array of keys)
    int *count_array;
    count_array = (int *)malloc(sizeof(int) * length);
    *count_array = make_count_array(src, length, count_array);

    // Make src without spaces to take symbol from
    char *raw_src;
    raw_src = (char *)malloc(sizeof(char) * (length_of_dest_array - length));
    *raw_src = make_src_without_spaces(src, (length_of_dest_array - length), raw_src);

    // Array for save in what index first element of each string will be insert
    int new_ind[length];
    for(int i = 0; i < length; i++) new_ind[i] = 0;

    // The sorting itself
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (count_array[i] <= count_array[j]) {
                new_ind[j] += count_array[i] + 1;
            } else {
                new_ind[i] += count_array[j] + 1;
            }
        }
    }

    dest[length_of_dest_array - 1] = '\0';

    int j = 0;
    int k = 0;
    int ind_from_raw_src = 0;
    for(int i = 0; i < length_of_dest_array - 1; i++) {
        if(k == count_array[j]) {
            if(new_ind[j] + k != length_of_dest_array - 1) {
                dest[new_ind[j] + k] = ' ';
                i++;
            }
            k = 0;
            j++;
            if(j > length - 1) break;
        }
        dest[new_ind[j] + k] = raw_src[ind_from_raw_src];
        k++;
        ind_from_raw_src++;

    }

    // Clearing the memory
    free(raw_src);
    free(count_array);
}


int main()
{
    char src[BUFFER_SIZE];
    fgets(src, BUFFER_SIZE, stdin);
    char dest[length_of_dest(src)];

    csort(src, dest);

    printf("%s\n", dest);
    return 0;
}
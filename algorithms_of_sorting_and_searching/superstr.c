#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#define BUFFER_SIZE 10000
#define MAX_SIZE 10 // Maximum number of elements in the 2-d array

char keys[MAX_SIZE][MAX_SIZE] = {}; // Array to store the keys 


void init_keys()
{
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            keys[i][j] = -1;
        }
    }
}


void scan_array_of_strings(char **words, size_t length)
{
    for(int i = 0; i < length; i++) {
        char word[BUFFER_SIZE];
        scanf("%s", word);
        words[i] = (char *)malloc(strlen(word) + 1);
        strcpy(words[i], word);
    }
}


void swap(char **words, int indexes[], int i, int j) 
{
	char *temp = words[i];
    words[i] = words[j];
    words[j] = temp;

    int temp_ind = indexes[i];
    indexes[i] = indexes[j];
    indexes[j] = temp_ind;

}


int is_ends_with(char s1[], char s2[])
{
    int n1 = strlen(s1), n2 = strlen(s2);
    int i = 0;
    while(i < n1) {
        int j;
        int k = 0;
        bool is_suffix_start = false;
        int count_to_sub = 0;
        for(j = i; j < n1; j++) {
            if(s1[j] == '\0' || s1[j] == '\n' || s2[k] == '\0' || s2[k] == '\n') {
                break;
            }
            if(s1[j] == s2[k]) {
                is_suffix_start = true;
                count_to_sub++;
                k++;
            } else {
                break;
            }
        }
        if(is_suffix_start && j == n1) {
           return count_to_sub;
        }
        i++;
    }
    return 0;
}


int get_len_of_shortest_string(char **words, int indexes[], size_t length)
{
    if(length < 1) {
        return -1;
    }
    int count = strlen(words[0]);
    for(int i = 1; i < length; i++) {
        count += strlen(words[i]);
        int val = keys[indexes[i - 1]][indexes[i]];
        if(val != -1) {
            count -= val;
            continue;
        }
        int res = is_ends_with(words[i - 1], words[i]);
        count -= res;
        keys[indexes[i - 1]][indexes[i]] = res;
    }
    return count;
}


void permut(char **words, int indexes[], int start, int end, size_t length, int *min) 
{
	int i;
	if (start == end) {
        int len_of_shortest_string = get_len_of_shortest_string(words, indexes, length);
        if(len_of_shortest_string != -1 && len_of_shortest_string < *min) {
            *min = len_of_shortest_string;
        }
        return;
    }
	else {
		for (i = start; i <= end; i++) { 
			swap(words, indexes, start, i);
			permut(words, indexes, start + 1, end, length, min);
			swap(words, indexes, start, i);
		}
	}
    return;
}


int main() 
{
    int n;
    int min = INT_MAX;
    scanf("%d", &n);
    char **words = (char **)malloc(sizeof(char *) * n);
    int indexes[n];
    for(int i = 0; i < n; i++) {
        indexes[i] = i;
    }
    init_keys();
    scan_array_of_strings(words, n);

    permut(words, indexes, 0, n - 1, n, &min);

    printf("%d\n", min);

    // Clearing the memory
    for(int i = 0; i < n; i++) free(words[i]);
    free(words);

	return 0;
}
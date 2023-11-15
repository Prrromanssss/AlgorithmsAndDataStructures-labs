#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define SIZE 10

typedef long long big_size;

void scan_array(big_size array[SIZE][SIZE], int row, int column)
{
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            scanf("%lld", &array[i][j]);
        }
    }
}


void init_arrays_with_max_min_variables(big_size max_rows[], big_size min_columns[], int row, int column)
{
    for(int i = 0; i < row; i++)
		max_rows[i] = LLONG_MIN;

	for(int i = 0; i < column; i++)
		min_columns[i] = LLONG_MAX;
}


int is_contains(big_size elem, big_size array[], size_t length)
{
    for(int i = 0; i < length; i++) {
        if(array[i] == elem) {
            return i;
        }
    }
    return -1;
}


void fill_arrays_with_max_min_variables(
    big_size array[SIZE][SIZE], big_size max_rows[], big_size min_columns[],
    int row, int column)
{
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            big_size current_elem = array[i][j];
            max_rows[i] = (max_rows[i] < current_elem) ?
                           current_elem : max_rows[i];
			min_columns[j] = (min_columns[j] > current_elem) ?
                              current_elem : min_columns[j];
        }
    }
}


void print_index_saddlepoint_or_none(big_size max_rows[], big_size min_columns[], int row, int column)
{
    int coord_i = 0, coord_j = 0;
    bool is_saddlepoint_exist = false;
    for(int i = 0; i < row; i++) {
        int contain = is_contains(max_rows[i], min_columns, column);
        if(contain != -1) {
            coord_i = i;
            coord_j = contain;
            is_saddlepoint_exist = true;
            break;
        }
    }
    if(is_saddlepoint_exist) printf("%d %d\n", coord_i, coord_j);
    else printf("none\n");
}


int main() {
    int row, column;
    scanf("%d %d", &row, &column);

    big_size array[SIZE][SIZE];
    big_size max_rows[row];
    big_size min_columns[column];

    // scanning array
    scan_array(array, row, column);

    init_arrays_with_max_min_variables(max_rows, min_columns, row, column);
    fill_arrays_with_max_min_variables(array, max_rows, min_columns, row, column);
    print_index_saddlepoint_or_none(max_rows, min_columns, row, column);

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_contains(int elem, int array[], size_t length)
{
    for(int i = 0; i < length; i++) {
        if(array[i] == elem) {
            return true;
        }
    }
    return false;
}


int main() {
    int row, column;
    scanf("%d %d", &row, &column);
    int array[10][10];
    int max_rows[row];
    int min_columns[column];

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    for(int i = 0; i < row; ++i)
		max_rows[i] = INT_MIN;

	for(int i = 0; i < column; i++)
		min_columns[i] = INT_MAX;

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            int current_elem = array[i][j];

            max_rows[i] = (max_rows[i] < current_elem) ?
                           current_elem : max_rows[i];
			min_columns[j] = (min_columns[j] > current_elem) ?
                              current_elem : min_columns[j];
        }
    }

    int saddlepoint = 0;
    int is_saddlepoint_exist = false;
    for(int i = 0; i < row; i++) {
        if(is_contains(max_rows[i], min_columns, column)) {
            saddlepoint = max_rows[i];
            is_saddlepoint_exist = true;
            break;
        }
    }

    if(is_saddlepoint_exist) printf("%d\n", saddlepoint);
    else printf("none");
    return 0;
}
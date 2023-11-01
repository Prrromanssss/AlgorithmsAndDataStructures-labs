#include <stdio.h>
#include <stdbool.h>

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
    int array[row][column];
    int transpose_array[column][row];
    int max_rows[row];
    int min_columns[column];

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    for(int i = 0; i < row; i++) {
        int max_elem_in_row = 0;

        for(int j = 0; j < column; j++) {
            int current_elem = array[i][j];

            if(current_elem > max_elem_in_row) {
                max_elem_in_row = current_elem;
            }
        }
        max_rows[i] = max_elem_in_row;
    }

    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++)
            transpose_array[i][j] = array[j][i];
    }

    for(int i = 0; i < column; i++) {
        int min_elem_in_column = 9999999;

        for(int j = 0; j < row; j++) {
            int current_elem = transpose_array[i][j];

            if(current_elem < min_elem_in_column) {
                min_elem_in_column = current_elem;
            }
        }
        min_columns[i] = min_elem_in_column;
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
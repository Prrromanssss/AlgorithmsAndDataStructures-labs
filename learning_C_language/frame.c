#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BUFFER_SIZE 10001


void draw_paint(int x, int y, char *word, int length)
{
    int top_indent = (int)ceil((x - 2) / 2.0);
    int left_indent = (y - 2 - length) / 2 + 1;
    int right_indent = left_indent + length - 1;
    int k = 0;
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            if(i == 0 || i == x - 1) {
                printf("*");
            } else if(j == 0 || j == y - 1) {
                printf("*");
            } else if(j <= right_indent && i == top_indent && j == left_indent) {
                printf("%c", word[k]);
                k++;
                left_indent++;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}


int main(int argc, char *argv[])
{
    if(argc < 4) {
        printf("Usage: frame <height> <width> <text>");
        return 0;
    }
    int y = atoi(argv[1]), x = atoi(argv[2]);

    if(x - 2 < strlen(argv[3])) {
        printf("Error");
        return 0;
    }

    draw_paint(y, x, argv[3], strlen(argv[3]));

    return 0;
}

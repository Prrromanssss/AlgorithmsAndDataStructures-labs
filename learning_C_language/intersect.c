#include <stdio.h>
#include <math.h>

void dec2bin(unsigned long num)
{
    int bin = 0, i = 0;
    while (num) {
        bin = num % 2;
        if(bin) printf("%d ", i);
        i++;
        num /= 2;
    }
}

unsigned long set_input() {
    int len;
    scanf("%d", &len);
    unsigned long set = 0;
    unsigned long elem;
    for(int i = 0; i < len; i++) {
        scanf("%lu", &elem);
        set += pow(2, elem);
    }
    return set;
}


int main() {
    unsigned long a = set_input();
    unsigned long b = set_input();
    unsigned long res = a & b;
    dec2bin(res);
    return 0;
}
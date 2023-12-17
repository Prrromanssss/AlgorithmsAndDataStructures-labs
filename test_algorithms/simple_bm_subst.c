#include <stdio.h>


#define SIZE 256


typedef struct StringWithLength {
    char *data;
    int length;
} str_l;


void delta1(str_l s, int size, int d1[])
{
    for(int a = 0; a < size; a++) {
        d1[a] = s.length;
    }
    for(int j = 0; j < s.length - 1; j++) {
        d1[s.data[j]] = s.length - j - 1;
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int simple_bm_subst(str_l s, int size, str_l t)
{
    int d1[size];
    delta1(s, size, d1);
    int k = s.length - 1;
    int i;
    while(k < t.length) {
        i = s.length - 1;
        while(t.data[k] == s.data[i]) {
            if(i == 0) {
                return k;
            }
            i--;
            k--;
        }
        k = k + max(d1[t.data[k]], s.length - i);
    }

    return t.length;

    
}


int main()
{
    str_l t = {"which'finally'halts'''at'that'point", 35};
    str_l s = {"at'that", 7};

    printf("%d ", simple_bm_subst(s, SIZE, t));

    return 0;
}
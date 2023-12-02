#include <stdio.h>
#include <string.h>


char *fibstr(int n)
{
    if(n == 1) {
        return 'a';
    }
    if (n == 2) {
        return 'b';
    }
    return strcat(fibstr(n - 2), fibstr(n - 1));
}


int main()
{
    
}
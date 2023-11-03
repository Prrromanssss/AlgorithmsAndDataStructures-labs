unsigned long binsearch(unsigned long nel, int(*compare)(unsigned long i))
{   
    int M;
    int L = -1;
    int R = nel;
    while(R - L > 1) {
        M = (R + L) / 2;
        int temp = compare(M);
        if(temp == -1)
            L = M;
        if(temp == 0)
            return M;
        if(temp == 1)
            R = M;
    }
    return nel;
}
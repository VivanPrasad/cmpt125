#include <stdio.h>

int findMax(int x, int y); // Function prototype

int main(void) {

    short a = 3;
    short b = 4;
    int max = findMax(a,b);

    printf("\n%d",max);
    return 0;
}

int findMax(int x, int y) 
{
    return (x > y) ? x : y;
}
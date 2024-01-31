#include <stdio.h>
#include <stdlib.h>

void display_pattern(int rows) 
{
    int value = 0;
    const int columns = 2*rows + 1;
    for (int r=1; r <= rows; r++)
    {
        for (int c=1; c <= columns; c++)
        {
            if (c>(rows-r+1) && c<=(columns-r))
            {
                value += 1;
                printf(" %-3d",value);
            }
            else {printf(" %-3d",0);}
        }
        printf("\n");
    }
}
int main(void)
{
    int N; // For the number of rows
    printf("Enter the number of rows in the pattern ");
    scanf("%d",&N);
    if (N > 9 || N < 2) {
        fprintf(stderr,"ERROR: %s\n","Value of N supplied is out of range");
        exit(1);
    }

    display_pattern(N);
    return 0;
}
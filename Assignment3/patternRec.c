#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_TRIES 5 //Number of prompt attempts

/*Prompts user for number of rows; 5 tries*/
int getNumRows(int *rows)
{
    for (int i=1;i<=NUM_TRIES;i++)
    {
        fprintf(stdout, "Enter the number of rows: ");
        scanf("%d",rows); // Range Handling
        
        //Exit loop if in range
        if (*rows >= 1 && *rows <= 20) break;
        
        if (i!=NUM_TRIES) // Incorrect Range Error
        {
            fprintf(stderr,"ERROR: The number of rows \
is out of range.\n%7s1 <= number of rows <= 20\n"," ");
        } else //Last Attempt Incorrect Error
        {
            fprintf(stderr,"ERROR: Too many tries \
attempting to read the number of rows for the pattern.\n");
            return EXIT_FAILURE;
        }
    }
    //If Neven and N != 1, Neven act same as N-1 (so Nodd) 
    if ((*rows%2) == 0 && *rows != 1) *rows -= 1;
}

/*Returns the pattern value from given n 
using summation, n(n+1)/2*/
int getTriangularNum(int n)
{
    return ( ( n*(n+1) ) / 2 );
}

/*Prints pattern cell, printing 
empty space if value < 1*/
void printPatternCell(int value)
{
    if (value > 0) fprintf(stdout,"%5d",value);
    else fprintf(stdout,"%5s"," ");
}

/*Prints pattern row recursively
by calling printPatternCell*/
void printPatternRow(int rowsLeft, int numRows)
{
    if (rowsLeft < 1) return; //Base case
    int currentRow = numRows - rowsLeft;
    int value = 0;
    for (int i=0;i<numRows;i++)
    {
        if (currentRow > rowsLeft) 
        {
            if (i <= ((numRows/2)+(rowsLeft-1)) 
             && i >= ((numRows/2)-(rowsLeft-1)))
            {
                if (i>(numRows/2)) value -= 1;
                else value += 1;
            } 
            else value = 0;
        }
        else
        {
            if (i <= ((numRows/2)+currentRow) 
             && i >= ((numRows/2)-currentRow)) 
            {
                if (i>(numRows/2)) value -= 1;
                else value += 1; 
            } 
            else value = 0;
        }
        //Prints the triangular number value of cell > 0
        printPatternCell(getTriangularNum(value));
    }
    printf("\n"); //Newline after row is completed
    printPatternRow(rowsLeft-1,numRows); //Recursive
}

int main(void)
{
    int numRows;
    getNumRows(&numRows); // Prompts and gets numRows
    printPatternRow(numRows,numRows);
    return 0;
}
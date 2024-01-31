#include <stdio.h>
#include <stdlib.h>
int  NextGen(char **lifeBoard, int numRowsInBoard, int numColsInBoard)
{
    /*This program takes the lifeboard and calculates
      another board in which it places the next generation
      The new generation is then copied back into lifeboard
      to be returned to the calling progran
      Author Janice Regan; 2024
	*/

    const char organism = 'X';      // to compare for organisms
    int neighborcount;              // used to count the neighbors 
	char **nextGenBoard = NULL;

	nextGenBoard = (char **)malloc(numRowsInBoard * sizeof(char*));
	if (nextGenBoard == NULL)
	{
		printf("array of pointer for myLifeBoard could not be allocated\n");
		return 100;
	}
	nextGenBoard[0] = (char *)malloc(numRowsInBoard*numColsInBoard * sizeof(char));
	if (nextGenBoard[0] == NULL)
	{
		printf("array for myLifeBoard could not be allocated\n");
		free(nextGenBoard);
		return 100;
	}
	for (int i = 1; i < numRowsInBoard; i++)
	{
		nextGenBoard[i] = nextGenBoard[0] + i * numColsInBoard;
	}


    /* step over each element except edge elements  
       This function assumes that the edge elements are not organisms 
       It is the responsibility of the user to supply input that does 
       not include organisms on its boundaries */  
    for (int indexrow = 1; indexrow <= numRowsInBoard - 2; indexrow++)
    {
        for (int indexcol = 1; indexcol <= numColsInBoard - 2; indexcol++)
        {
            neighborcount = 0;
            /* determine now many neighbors this element has 
               individually check each adjacent element to see 
               if it is an organism 
               increment the counter if it is  */
            for (int i=-1;i<=1;i++) {
                for (int k=-1;k<=1;k++) {
                    if (lifeBoard[indexrow+i][indexcol+k] == organism) {
                        neighborcount++;}
                }
            }

            /* apply the rules to determine if this location 
               should hold an organism in the next generation */ 
            switch (neighborcount)
            {
                case 2: 
                    nextGenBoard[indexrow][indexcol] = 
                        lifeBoard[indexrow][indexcol];
                    break;
                case 3: 
                    nextGenBoard[indexrow][indexcol] = organism;
                    break;
                default:
                    nextGenBoard[indexrow][indexcol] = '.';
                    break;
            }

        }
    }



    /* copy the new generation array into the lifeBoard array 
       note that the elements on the edges of the arrays are  
       not being copied.  The edge elements are not fertile   
       they can never contain organisms, so they do not need  
       to be updated */
    for (int indexrow = 1; indexrow <= numRowsInBoard - 2; indexrow++)
    {
        for (int indexcol = 1; indexcol <= numColsInBoard - 2; indexcol++)
        {
            lifeBoard[indexrow][indexcol] =
                nextGenBoard[indexrow][indexcol];
        }
    }
	free(nextGenBoard[0]);
	free(nextGenBoard);
	return 0;
}
int main(void)
{
    NextGen();
    return 0;
}
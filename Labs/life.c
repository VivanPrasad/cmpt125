#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

const int MAX_ARRAY_SIZE = 40;

int  NextGen(char lifeBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard)
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
                    if (lifeBoard[indexrow+i][indexcol+k] == organism && !((i==0)&&(k==0))) {
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

void printGen(char lifeBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], FILE *outStream, int numRowsInBoard, int numColsInBoard, int generationNum)
{

    for (int currentGen=0;currentGen<=generationNum;currentGen++)
    {
        if (currentGen > 0)
        {
            if (currentGen == generationNum || currentGen == 1) 
            {
                printf("LIFE game board generation %i\n",currentGen);
            }   
            fprintf(outStream,"LIFE game board generation %i\n",currentGen);
            NextGen(lifeBoard,numRowsInBoard,numColsInBoard);
        }
        else 
        {
            fprintf(outStream,"LIFE initial game board\n");
            printf("LIFE initial game board\n");
        }

        for (int r=0;r<numRowsInBoard;r++)
        {
            for (int c=0;c<numColsInBoard;c++)
            {
                fprintf(outStream,"%c ",lifeBoard[r][c]);
                if (currentGen == generationNum || currentGen <=1)
                {
                    printf("%c ",lifeBoard[r][c]);
                }
            }
            fprintf(outStream,"\n");
            if (currentGen == generationNum || currentGen <= 1)
                {
                    printf("\n");
                }
        }
    }
}
    

int main(void) //main scope oOOOOoOOo
{
    
    FILE *inputFile = NULL; //input
    FILE *outputFile = NULL;    
    char inputFileName[16];
    char outputFileName[16];

    int rows; //number of rows in the grid
    int columns; // number of columns in the grid
    int generations; //number of generations
    char myLifeBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];//MAX_ARRAY_SIZE=40

    for (int i=1; i<=4; i++) //Read Contents of File
    {
        printf("Enter the name of the input file: ");
        scanf("%s",&inputFileName);
        inputFile = fopen(inputFileName,"r");
        if (inputFile == NULL) 
        {
            fprintf(stderr,"ERROR: input file not opened correctly\n");
            if (i==4) //After 4 tries, if the file is still NULL, exit code 1
            {
                fprintf(stderr,"ERROR: too many incorrect file names\n"); 
                exit(1);
            }
            continue;
        }
        else {break;}
    }
    fscanf(inputFile,"%d",&rows);
    if (rows>=40 || rows<=0)
        {
            fprintf(stderr,"ERROR: Read an illegal number of rows for the board\n");
            return 1;
        }
    fscanf(inputFile,"%d",&columns);
    if (rows>=40 || rows<=0) 
    {
        fprintf(stderr,"ERROR: Read an illegal number of rows for the board\n");
        return 1;
    }
    fscanf(inputFile,"%d",&generations);
    if (generations<0) 
    {
        fprintf(stderr,"ERROR: Read an illegal number of rows for the board\n");
        return 1;
    }
    
    //printf("%d %d %d\n",rows,columns,generations);
    fscanf(inputFile,"\n\n","");
    for (int a=0;a<rows;a++)
    {
        for (int b=0;b<columns;b++)
        {
            fscanf(inputFile,"%c ",&myLifeBoard[a][b]);
            int value = myLifeBoard[a][b];
            if (value == 0 && (a==0 || b==0))
            {
                fprintf(stderr,"\nERROR: organisms are present in the border of the board, please correct your input file");
                exit(1);
            }
            else if (!value == 46 && !value == 88)
            {
                fprintf(stderr,"\nERROR: Input data for initial board is incorrect\nLocation (%i, %i) is not valid",a,b);
                exit(1);
            }
            else if (feof(inputFile) && (a<(rows-1) || b<(columns-1))) 
            {
                fprintf(stderr,"\nERROR: Not enough data in the input file");
                exit(1);
            }
        }
    }

    fclose(inputFile);
    //----------------------------------------------------------

    for (int k=1; k<=4; k++) //Read Contents of File
    {
        printf("Enter the name of the output file: ");
        scanf("%s",&outputFileName);
        outputFile = fopen(outputFileName,"w");
        if (outputFile == NULL) 
        {
            fprintf(stderr,"ERROR: output file not opened correctly\n");
            if (k==4) //After 4 tries, if the file is still NULL, exit code 1
            {
                fprintf(stderr,"ERROR: too many incorrect file names\n"); 
                exit(1);
            }
            continue;
        }
        else {break;}
    }

    printGen(myLifeBoard,outputFile,rows,columns,generations);
    //some issue with myLifeBoard not being char **
    
    fclose(outputFile);
    return 0;
}
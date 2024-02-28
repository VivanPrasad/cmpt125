#include <stdio.h>
#include <stdlib.h>

// COLORS
#define WHITE "\e[38;5;7m"
#define RED "\e[38;5;1m"
#define GREEN "\e[38;5;10m"
#define BLUE "\e[0;34m"

#define NUM_COLORS 4 // Number of board colors
#define NUM_DIRECTIONS 4
#define FILE_TEXT_LENGTH 100

enum initTypeList { Random=1, Checker=2, AllWhite=3};

struct Robot {
    int x, y;
    int direction;
    int paintColor;
};

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols); 
void InitBoardAllWhite(int **board, int numRows, int numCols); 

int InitBoard(int **board, int numRows, int numCols, enum initTypeList initTypeValue, unsigned int seed);
int InitRobots(struct Robot *robots, int numRows, int numCols, int numRobots,unsigned int seed);

int nextBoard(int **board, int numRows, int numCols, int numRobots, struct Robot *robots);

void printBoard(FILE *stream, int **board, int numRows, int numCols, int numRobots);
void printBoardColored(FILE *stream, int **board, int numRows, int numCols, int numRobots);

int main(void)
{
    FILE* inputFile = NULL; // File to import data
    char inputName[FILE_TEXT_LENGTH]; 
    
    FILE* outputFile = NULL; // File to export data
    char outputName[FILE_TEXT_LENGTH]; 

    int numRows, numCols; // 50 to 300 inclusive
    int numRobots; // 1 to 10 inclusive
    enum initTypeList initTypeValue; // 1 to 3 inclusive
    unsigned int initSeed; //10 to 32767 inclusive
    int numTurns; //10 to 5000 inclusive
    int printInterval; // 1 to turns inclusive

    for (int attempt=1;attempt<=5;attempt++) // 5 attempts to read input file
    {
        printf("Enter the name of the input file: ");
        scanf("%s",inputName);
        inputFile = fopen(inputName,"r");
        if (inputFile==NULL)
        {
            printf("ERROR: Input file not opened correctly.\n");
            if (attempt==5)
            {
                printf("ERROR: Failed to open the input file 5 times. Terminating the program.\n");
                return 1;
            }
        } else break;
    }
    
                                    /* NUMBER OF ROWS READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The number of rows was not in the input file (reached eof)\n");
        return 1;
    }
    if (fscanf(inputFile,"%d\n",&numRows)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The number of rows could not be read due to corrupt data in the file\n");
    }
    if (numRows < 20 || numRows > 300) // Check range
    {
        fprintf(stderr,"ERROR: The number of rows was outside the specified range (50 to 300 inclusive)\n");
        return 1;
    }

                                    /* NUMBER OF COLUMNS READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The number of columns was not in the input file (reached eof)\n");
        return 1;
    }
    
    if (fscanf(inputFile,"%d\n",&numCols)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The number of columns could not be read due to corrupt data in the file\n");
        return 1;
    }
    if (numCols < 20 || numCols > 300) // Check range
    {
        fprintf(stderr,"ERROR: The number of columns was outside the specified range (50 to 300 inclusive)\n");
        return 1;
    }

                                    /* NUMBER OF ROBOTS READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The number of robots was not in the input file (reached eof)\n");
        return 1;
    }
    if (fscanf(inputFile,"%d\n",&numRobots)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The number of robots could not be read due to corrupt data in the file\n");
        return 1;
    }
    if (numRobots < 1 || numRobots > 10) // Check range
    {
        fprintf(stderr,"ERROR: The number of robots was outside the specified range (1 to 10 inclusive)\n");
        return 1;
    }

                                        /* BOARD TYPE READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
        return 1;
    }
    if (fscanf(inputFile,"%u\n",&initTypeValue)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The initTypeValue could not be read due to corrupt data in the file\n");
        return 1;
    }
    if (initTypeValue < 1 || initTypeValue > 3) // Check range
    {
        fprintf(stderr,"ERROR: The initTypeValue was outside the specified range (1 to 3 inclusive)\n");
        return 1;
    }

                                        /* SEED READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The initSeed was not in the input file (reached eof)\n");
        return 1;
    }
    if (fscanf(inputFile,"%u\n",&initSeed)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The initSeed could not be read due to corrupt data in the file\n");
        return 1;
    }
    if (initSeed < 10 || initSeed > 32767) // Check range
    {
        fprintf(stderr,"ERROR: The initSeed was outside the specified range (10 to 32767 inclusive)\n");
        return 1;
    }

                                    /* NUMBER OF TURNS READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The number of turns was not in the input file (reached eof)\n");
        return 1;
    }
    if (fscanf(inputFile,"%d\n",&numTurns)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The number of turns could not be read due to corrupt data in the file\n");
        return 1;
    }
    if (numTurns < 10 || numTurns > 5000) // Check range
    {
        fprintf(stderr,"ERROR: The number of turns was outside the specified range (10 to 5000 inclusive)\n");
        return 1;
    }

                                    /* PRINT INTERVAL READING */
    if (feof(inputFile)) // Check if end of file
    {
        fprintf(stderr,"ERROR: The printInterval was not in the input file (reached eof)\n");
        return 1;
    }
    if (fscanf(inputFile,"%d\n",&printInterval)==0) // Check reading
    {
        fprintf(stderr,"ERROR: The printInterval could not be read due to corrupt data in the file\n");
        return 1;
    }
    if (printInterval<1||printInterval>5000) // Check range
    {
        fprintf(stderr,"ERROR: The printInterval was outside the specified range (1 to 5000 inclusive)\n");
        return 1;
    }

                                /* OUTPUT FILE NAME READING */
    if (feof(inputFile)) 
    {
        fprintf(stderr,"ERROR: Output file name was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%s\n",outputName);
    outputFile = fopen(outputName,"w"); // Open and make the export file

    fclose(inputFile);

    /*------------GAME SETUP STUFF------------*/

    int **boardpp = NULL; // BOARD SETUP
    boardpp = (int**)malloc(numRows*sizeof(int*));
    if (boardpp == NULL)
	{
		fprintf(stderr,"ERROR: array of pointers for 2-D array could not be allocated\n");
        fprintf(outputFile,"ERROR: array of pointers for 2-D array could not be allocated\n");
		return 100;
	}
	boardpp[0] = (int*)malloc(numRows*numCols*sizeof(int));
	if (boardpp[0] == NULL)
	{
		fprintf(stderr,"ERROR: Array storage could not be allocated\n");
        fprintf(outputFile,"ERROR: Array storage could not be allocated\n");
		free(boardpp);
		return 100;
	}
	for (int i=1;i<numRows;i++)
	{
		boardpp[i] = boardpp[0] + (i*numCols);
	}
    InitBoard(boardpp,numRows,numCols,initTypeValue,initSeed);

    struct Robot *robots = NULL; // ROBOT SETUP
    robots = (struct Robot*)malloc(numRobots*sizeof(struct Robot)); // Declare dynamic array of robots
    if (robots == NULL)
    {
        fprintf(stderr,"ERROR: Array storage could not be allocated\n");
        fprintf(outputFile,"ERROR: Array storage could not be allocated\n");
        free(robots); robots = NULL;
		return 100;
    }
    InitRobots(robots,numRows,numCols,numRobots,initSeed);

    nextBoard(boardpp,numRows,numCols,numRobots,robots);
    
    for (int t=1;t<=numTurns;t++)
    {
        if (t==1 || t==(numTurns) || (t%printInterval==0)) 
        {
            printBoardColored(stdout,boardpp,numRows,numCols,numRobots);
            printBoard(outputFile,boardpp,numRows,numCols,numRobots);
        }
        nextBoard(boardpp,numRows,numCols,numRobots,robots);
    }

    fclose(outputFile);
    free(robots); robots = NULL;
    free(boardpp); boardpp = NULL;
    free(boardpp[0]); boardpp[0] = NULL;
    
    return 0;
}

int InitRobots(struct Robot *robots, int numRows, int numCols, int numRobots,unsigned int seed)
{
    srand(seed); // Initialize the random number generator
    for (int i=0;i<numRobots;i++) // Initialize each robot at a random position, direction and color
    {
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;
        robots[i].direction = rand() % NUM_DIRECTIONS + 1;
        robots[i].paintColor = rand() % NUM_COLORS + 1;
    }
    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList initTypeValue, unsigned int seed)
{
    switch (initTypeValue)
    {
        case 1:
            InitBoardRand(boardpp,numRows,numCols,seed); break;
        case 2:
            InitBoardChecker(boardpp,numRows,numCols); break;
        case 3:
            InitBoardAllWhite(boardpp,numRows,numCols); break;
        default: break;
    }
    return 0;
}

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed)
{
    srand(seed);
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            board[r][c] = rand() % NUM_COLORS + 1;
        }
    }
}
void InitBoardChecker(int **board, int numRows, int numCols)
{
    int checkerColor;
    for (int r=0;r<numRows;r++)
    {
        if (r%2==0) checkerColor = 1;// White on even rows
        else checkerColor = 2; // Red on odd rows
        for (int c=0;c<numCols;c++)
        {
            board[r][c] = checkerColor;
            checkerColor = ((checkerColor)%2)+1; // Alternate White and Red 
        }
    }
}
void InitBoardAllWhite(int **board, int numRows, int numCols)
{
    for (int r=0;r<numRows;r++) 
    {
        for (int c=0;c<numCols;c++) 
        {
            board[r][c] = 1;
        }
    }
}

/* BOARD SIMULATION FUNCTIONS */
int nextBoard(int **board, int numRows, int numCols, int numRobots, struct Robot *robots)
{
    int current_tile; //Color of the tile the robot is standing on AFTER moving
    for (int i=0;i<numRobots;i++)
    {
        current_tile = board[robots[i].y][robots[i].x];
        board[robots[i].y][robots[i].x] = robots[i].paintColor;
        switch (robots[i].direction)
        {
            case 1: // Robot moves NORTH
                if (robots[i].y > 0) robots[i].y -= 1;
                else robots[i].y = numRows-1; // Loops around board
                break;
            case 2: // Robot moves EAST
                if (robots[i].x < (numCols-1)) robots[i].x += 1;
                else robots[i].x = 0; // Loops around board 
                break;
            case 3: // Robot moves SOUTH
                if (robots[i].y < (numRows-1)) robots[i].y += 1;
                else robots[i].y = 0; // Loops around board
                break;
            case 4: // WEST
                if (robots[i].x > 0) robots[i].x -= 1;
                else robots[i].x = numCols-1; // Loops around board
                break;
        }
        current_tile = board[robots[i].y][robots[i].x];
        robots[i].direction = (robots[i].direction+current_tile-1)%4 + 1;
    }
    return 0;
}
/*----------OUTPUT FUNCTIONS----------*/
// Prints board state to stdout (colored)
void printBoardColored(FILE* stream, int **board, int numRows, int numCols, int numRobots)
{
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            switch (board[r][c])
            {
                case 1: fprintf(stream,WHITE"%d",board[r][c]); 
                    break;
                case 2: fprintf(stream,RED"%d",board[r][c]); 
                    break;
                case 3: fprintf(stream,GREEN"%d",board[r][c]); 
                    break;
                case 4: fprintf(stream,BLUE"%d",board[r][c]); 
                    break;
            }
        }
        printf("\n");
    }
    printf(WHITE"\n\n");
}

// Prints board state to outputFile
void printBoard(FILE *stream, int **board, int numRows, int numCols, int numRobots)
{
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            fprintf(stream,"%d",board[r][c]);
        }
        fprintf(stream,"\n");
    }
    fprintf(stream,"\n\n");
}
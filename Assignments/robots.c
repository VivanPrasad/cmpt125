#include <stdio.h>
#include <stdlib.h>

// COLORS
#define WHITE "\e[38;5;7m"
#define RED "\e[38;5;1m"
#define GREEN "\e[38;5;10m"
#define BLUE "\e[0;34m"

#define RESET "\e[1;1H\e[2J"

#define NUM_COLORS 4
#define NUM_DIRECTIONS 4
#define FILE_TEXT_LENGTH 100

#define ROBOT 64
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

void printSquare(int value);
void printRobot(int color);
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
    
    // NUMBER OF ROWS READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The number of rows was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%d\n",&numRows);
    if (numRows < 20 || numRows > 300)
    {
        fprintf(stderr,"ERROR: The number of rows was outside the specified range (50 to 300 inclusive)\n");
        return 1;
    }

    // NUMBER OF COLUMNS READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The number of columns was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%d\n",&numCols);
    if (numCols < 20 || numCols > 300)
    {
        fprintf(stderr,"ERROR: The number of columns was outside the specified range (50 to 300 inclusive)\n");
        return 1;
    }

    // NUMBER OF ROBOTS READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The number of robots was not in the input file (reached eof)\n");
    }
    fscanf(inputFile,"%d\n",&numRobots);
    if (numRobots < 1 || numRobots > 10)
    {
        fprintf(stderr,"ERROR: The number of robots was outside the specified range (1 to 10 inclusive)\n");
        return 1;
    }

    // BOARD TYPE READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
    }
    fscanf(inputFile,"%d\n",&initTypeValue);

    // SEED READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
    }

    fscanf(inputFile,"%u\n",&initSeed);
    fscanf(inputFile,"%d\n",&numTurns);
    fscanf(inputFile,"%d\n",&printInterval);

    // OUTPUT FILE NAME READING
    if (feof(inputFile)) 
    {
        fprintf(stderr,"ERROR: Output file name was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%s\n",&outputName);
    outputFile = fopen(outputName,"w"); // Open and make the export file

    fclose(inputFile);

    /*------------GAME SETUP STUFF------------*/

    int **boardpp = NULL; // BOARD SETUP
    boardpp = (int**)malloc(numRows*sizeof(int*));
    if (boardpp == NULL)
	{
		fprintf(stderr,"ERROR: array of pointers for could not be allocated\n");
        fprintf(outputFile,"ERROR: array of pointers for could not be allocated\n");
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

    for (int t=0;t<=numTurns;t++)
    {
        if (t==0 || t==(numTurns) || (t%printInterval==0)) 
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
        //printf("Robot %d - Pos: (%d, %d) - Dir: %d - Col: %d\n",
        //i+1,robots[i].x,robots[i].y,robots[i].direction,robots[i].paintColor);
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
            case 1: // NORTH
                if (robots[i].y > 0) robots[i].y -= 1;
                break;
            case 2: // SOUTH
                if (robots[i].y < (numRows-1)) robots[i].y += 1;
                break;
            case 3: // EAST
                if (robots[i].x < (numCols-1)) robots[i].x += 1;
                break;
            case 4: // WEST
                if (robots[i].x > 0) robots[i].x -= 1;
                break;
        }
        current_tile = board[robots[i].y][robots[i].x];
        robots[i].direction = (robots[i].direction+current_tile-1)%4 + 1;
    }
    return 0;
}
/*----------OUTPUT FUNCTIONS----------*/
// Prints board state to stdout
void printBoardColored(FILE* stream, int **board, int numRows, int numCols, int numRobots)
{
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            switch (board[r][c])
            {
                case 1: fprintf(stream,WHITE"%d"RESET,board[r][c]); 
                    break;
                case 2: fprintf(stream,RED"%d"RESET,board[r][c]); 
                    break;
                case 3: fprintf(stream,GREEN"%d"RESET,board[r][c]); 
                    break;
                case 4: fprintf(stream,BLUE"%d"RESET,board[r][c]); 
                    break;
            }
        }
        printf("\n");
    }
    printf("\n\n");
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